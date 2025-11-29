import os
import re
import sys
import json
import requests
from notion_client import Client

# ------------------------
# 配置：环境变量
# ------------------------
NOTION_API_KEY = os.environ.get("NOTION_TOKEN", "").strip()
PAGE_ID = os.environ.get("NOTION_PAGE_ID", "").strip()
CSDN_COOKIE = os.environ.get("CSDN_COOKIE", "").strip()

# GitHub 文件夹路径
OUTPUT_DIR = "LeetCode/Daily-Challenge"

if not NOTION_API_KEY or not PAGE_ID:
    print("❌ 错误：无法读取 NOTION_TOKEN 或 NOTION_PAGE_ID")
    sys.exit(1)

notion = Client(auth=NOTION_API_KEY)

# ------------------------
# CSDN 发布功能
# ------------------------
def push_to_csdn(title, content, category="LeetCode"):
    if not CSDN_COOKIE:
        print(f"   [CSDN] ⚠️ 未配置 CSDN_COOKIE，跳过发布。")
        return

    url = "https://blog-console-api.csdn.net/v1/mdeditor/saveArticle"
    
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
        "Cookie": CSDN_COOKIE,
        "Content-Type": "application/json",
        "Origin": "https://mp.csdn.net",
        "Referer": "https://mp.csdn.net/mp_blog/creation/editor"
    }

    data = {
        "title": title,
        "markdowncontent": content,
        "content": content,
        "read_type": "public",
        "status": 0,
        "not_auto_saved": "1",
        "source": "pc_mdeditor",
        "cover_type": 0,
        "categories": category,
        "type": "original"
    }

    try:
        response = requests.post(url, headers=headers, json=data)
        res_json = response.json()
        if res_json.get("code") == 200:
            print(f"   [CSDN] 🎉 成功发布文章: {title}")
        else:
            print(f"   [CSDN] ❌ 发布失败: {res_json.get('msg')}")
    except Exception as e:
        print(f"   [CSDN] ❌ 请求异常: {e}")

# ------------------------
# Notion 递归解析逻辑
# ------------------------

def richtext_to_plain(rich_text_list):
    if not rich_text_list:
        return ""
    text_content = ""
    for x in rich_text_list:
        plain = x.get("plain_text", "")
        # 处理行内公式 (Inline Equation)
        if x.get("type") == "equation":
            plain = f"${plain}$"
        # 处理链接
        if x.get("href"):
            plain = f"[{plain}]({x.get('href')})"
        text_content += plain
    return text_content

def get_block_children_recursive(block_id, depth=0):
    if depth > 5: # 递归深度限制
        return []
    results = []
    cursor = None
    while True:
        try:
            safe_id = block_id.replace("-", "")
            response = notion.blocks.children.list(safe_id, start_cursor=cursor)
            blocks = response.get("results", [])
            for block in blocks:
                if block.get("has_children", False):
                    block["children_blocks"] = get_block_children_recursive(block["id"], depth + 1)
                results.append(block)
            if not response.get("has_more"):
                break
            cursor = response.get("next_cursor")
        except Exception as e:
            print(f"⚠️ 获取子 Block 失败 (ID: {block_id}): {e}")
            break
    return results

def block_to_markdown(block):
    b_type = block["type"]
    content = ""
    text = ""
    if "rich_text" in block.get(b_type, {}):
        text = richtext_to_plain(block[b_type]["rich_text"])

    # 1. 标题处理
    if b_type == "heading_1":
        content = f"\n# {text}\n" 
    elif b_type == "heading_2":
        content = f"\n## {text}\n"
    elif b_type == "heading_3":
        content = f"\n### {text}\n"
        
    # 2. 基础文本
    elif b_type == "paragraph":
        content = f"{text}\n"
        
    # 3. 列表
    elif b_type == "bulleted_list_item":
        content = f"- {text}\n"
    elif b_type == "numbered_list_item":
        content = f"1. {text}\n"
    elif b_type == "to_do":
        checked = "x" if block["to_do"].get("checked") else " "
        content = f"- [{checked}] {text}\n"
        
    # 4. 折叠列表
    elif b_type == "toggle": 
        content = f"\n<details><summary>{text}</summary>\n\n"
        
    # 5. 引用
    elif b_type == "quote":
        content = f"> {text}\n"
        
    # 6. Callout (修复了这里崩溃的问题)
    elif b_type == "callout":
        callout_data = block.get("callout", {})
        # 安全获取 icon，防止 None 报错
        icon_data = callout_data.get("icon")
        icon = "💡"
        if icon_data and isinstance(icon_data, dict) and "emoji" in icon_data:
            icon = icon_data["emoji"]
        content = f"> {icon} **{text}**\n>\n"

    # 7. 代码块
    elif b_type == "code":
        lang = block["code"].get("language", "text")
        code_text = richtext_to_plain(block["code"]["rich_text"])
        content = f"\n```{lang}\n{code_text}\n```\n"
        
    # 8. 独立公式块 (Equation Block)
    elif b_type == "equation":
        expression = block["equation"].get("expression", "")
        content = f"\n$$\n{expression}\n$$\n"
        
    # 9. 分割线
    elif b_type == "divider":
        content = "\n---\n"

    # 递归处理子内容 (例如 Callout 内部的公式，或折叠列表里的内容)
    if "children_blocks" in block:
        for child in block["children_blocks"]:
            child_md = block_to_markdown(child)
            # 简单的缩进处理，让嵌套内容看起来更清晰
            if b_type in ["bulleted_list_item", "numbered_list_item"]:
                child_md = "  " + child_md.replace("\n", "\n  ")
            elif b_type == "callout":
                # Callout 内部内容全部加引用符号
                child_md = "> " + child_md.replace("\n", "\n> ")
            content += child_md
            
        if b_type == "toggle":
            content += "\n</details>\n"
            
    return content

# ------------------------
# 🗑️ 自动清理功能
# ------------------------
def clean_orphan_files(active_problem_numbers):
    """
    删除 GitHub 中存在，但 Notion 中已不存在（或已改名）的文件
    """
    if not os.path.exists(OUTPUT_DIR):
        return

    # 获取目录下所有 md 文件
    existing_files = [f for f in os.listdir(OUTPUT_DIR) if f.endswith(".md") and f != "README.md"]
    
    # 期望的文件名格式: Leetcode Daily challenge-{number}.md
    pattern = re.compile(r"Leetcode Daily challenge-(\d+)\.md")

    print("-" * 30)
    print("🧹 开始清理过期文件...")
    
    cleaned_count = 0
    for filename in existing_files:
        match = pattern.match(filename)
        if match:
            file_num = match.group(1)
            # 如果文件编号不在本次 Notion 解析到的编号列表中 -> 删除它
            if file_num not in active_problem_numbers:
                file_path = os.path.join(OUTPUT_DIR, filename)
                try:
                    os.remove(file_path)
                    print(f"🗑️ [删除] 过期文件: {filename} (Notion 中已删除或重命名)")
                    cleaned_count += 1
                except Exception as e:
                    print(f"⚠️ 删除失败 {filename}: {e}")
    
    if cleaned_count == 0:
        print("✨ 没有需要清理的文件。")

# ------------------------
# 主逻辑
# ------------------------
def parse_notion_page():
    print(f"🔗 连接 Notion 页面: {PAGE_ID[:4]}...")
    
    # 1. 递归获取内容
    all_root_blocks = get_block_children_recursive(PAGE_ID)
    
    if not all_root_blocks:
        print("❌ 未获取到内容")
        return

    print(f"🔍 获取到 {len(all_root_blocks)} 个根 Block")

    current_title = None
    current_content = []
    all_files = []

    # 2. 解析 Block
    for block in all_root_blocks:
        b_type = block["type"]
        text = ""
        if "rich_text" in block.get(b_type, {}):
            text = richtext_to_plain(block[b_type]["rich_text"])

        # 遇到一级标题 -> 视为新题目开始
        if b_type == "heading_1":
            # 如果之前有正在处理的题目，先保存
            if current_title:
                all_files.append((current_title, "".join(current_content)))
            
            current_title = text if text.strip() else "Untitled"
            current_content = []
            print(f"  👉 识别题目: {current_title}")
        else:
            # 遇到其他内容（H2, H3, 公式, 文本等） -> 视为当前题目的一部分
            # 这就是“自动归并到上一题”的核心逻辑
            md = block_to_markdown(block)
            current_content.append(md)

    # 保存最后一题
    if current_title:
        all_files.append((current_title, "".join(current_content)))

    # 用于记录本次所有有效的题号
    active_problem_numbers = set()

    print("-" * 30)
    for title, content in all_files:
        # 提取题号 (只认开头是数字的)
        match = re.search(r"^(\d{1,5})", title.strip())
        problem_number = match.group(1) if match else None
        
        if problem_number:
            # 记录有效题号
            active_problem_numbers.add(problem_number)

            file_path = os.path.join(OUTPUT_DIR, f"Leetcode Daily challenge-{problem_number}.md")
            os.makedirs(os.path.dirname(file_path), exist_ok=True)
            
            full_content = f"# {title}\n\n{content}"
            
            is_new_file = not os.path.exists(file_path)
            
            has_changed = False
            if not is_new_file:
                with open(file_path, "r", encoding="utf-8") as f:
                    if f.read().strip() != full_content.strip():
                        has_changed = True

            if is_new_file or has_changed:
                with open(file_path, "w", encoding="utf-8") as f:
                    f.write(full_content)
                
                if is_new_file:
                    print(f"✅ [GitHub] 新增: {file_path}")
                    push_to_csdn(title, full_content) 
                else:
                    print(f"✅ [GitHub] 更新: {file_path}")
            else:
                print(f"⏩ [GitHub] 无变化: {title}")
        else:
            print(f"⚠️ 跳过（无题号）: {title}")

    # 3. 执行清理 (只有脚本成功跑到这里，才会执行删除)
    if active_problem_numbers:
        clean_orphan_files(active_problem_numbers)
    else:
        print("⚠️ 本次未解析到任何有效题目，跳过清理步骤（防止误删）。")

if __name__ == "__main__":
    parse_notion_page()
