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
        return

    url = "https://blog-console-api.csdn.net/v1/mdeditor/saveArticle"
    headers = {
        "User-Agent": "Mozilla/5.0",
        "Cookie": CSDN_COOKIE,
        "Content-Type": "application/json",
        "Origin": "https://mp.csdn.net",
        "Referer": "https://mp.csdn.net/mp_blog/creation/editor"
    }
    data = {
        "title": title, "markdowncontent": content, "content": content,
        "read_type": "public", "status": 0, "not_auto_saved": "1",
        "source": "pc_mdeditor", "cover_type": 0, "categories": category, "type": "original"
    }
    try:
        response = requests.post(url, headers=headers, json=data)
        if response.json().get("code") == 200:
            print(f"   [CSDN] 🎉 成功发布: {title}")
        else:
            print(f"   [CSDN] ❌ 发布失败: {response.json().get('msg')}")
    except Exception:
        pass

# ------------------------
# Notion 解析逻辑 (核心)
# ------------------------

def richtext_to_plain(rich_text_list):
    if not rich_text_list:
        return ""
    text_content = ""
    for x in rich_text_list:
        try:
            plain = x.get("plain_text", "")
            # ✅ 增强：处理行内公式 (Inline Equation)
            if x.get("type") == "equation":
                expr = x.get("equation", {}).get("expression", plain)
                plain = f"${expr}$"
            # 处理链接
            elif x.get("href"):
                plain = f"[{plain}]({x.get('href')})"
            
            # 处理格式 (加粗/代码)
            annotations = x.get("annotations", {})
            if annotations.get("code"): plain = f"`{plain}`"
            elif annotations.get("bold"): plain = f"**{plain}**"
            elif annotations.get("italic"): plain = f"*{plain}*"
                
            text_content += plain
        except Exception:
            continue
    return text_content

def get_block_children_recursive(block_id, depth=0):
    if depth > 10: # 允许10层嵌套，足够处理折叠列表
        return []
    results = []
    cursor = None
    while True:
        try:
            safe_id = block_id.replace("-", "")
            response = notion.blocks.children.list(safe_id, start_cursor=cursor)
            blocks = response.get("results", [])
            for block in blocks:
                # 递归抓取 (处理折叠列表、Callout内部内容)
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
    # 🔥 防爆盾：单个 Block 解析失败不影响整体
    try:
        b_type = block["type"]
        content = ""
        text = ""
        
        # 提取文本
        if "rich_text" in block.get(b_type, {}):
            text = richtext_to_plain(block[b_type]["rich_text"])

        # 1. 标题
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
            
        # 4. 折叠列表 (Toggle)
        elif b_type == "toggle": 
            content = f"\n<details><summary>{text}</summary>\n\n"
            
        # 5. 引用
        elif b_type == "quote":
            content = f"> {text}\n"
            
        # 6. Callout (⚠️ 之前报错的地方已修复)
        elif b_type == "callout":
            callout_data = block.get("callout", {})
            # 安全获取 icon，防止 None 报错
            icon_data = callout_data.get("icon")
            icon = "💡" # 默认图标
            if icon_data and isinstance(icon_data, dict) and "emoji" in icon_data:
                icon = icon_data["emoji"]
            content = f"> {icon} **{text}**\n>\n"

        # 7. 代码块
        elif b_type == "code":
            lang = block["code"].get("language", "text")
            code_text = richtext_to_plain(block["code"]["rich_text"])
            content = f"\n```{lang}\n{code_text}\n```\n"
            
        # 8. 独立公式块 (Block Equation)
        elif b_type == "equation":
            expression = block.get("equation", {}).get("expression", "")
            content = f"\n$$\n{expression}\n$$\n"
            
        # 9. 分割线
        elif b_type == "divider":
            content = "\n---\n"
            
        # 10. 图片
        elif b_type == "image":
            url = block.get("image", {}).get("file", {}).get("url") or block.get("image", {}).get("external", {}).get("url")
            if url:
                content = f"![image]({url})\n"

        # 递归处理子内容 (Folded content / Callout content)
        if "children_blocks" in block:
            for child in block["children_blocks"]:
                child_md = block_to_markdown(child)
                # 缩进优化
                if b_type in ["bulleted_list_item", "numbered_list_item"]:
                    child_md = "  " + child_md.replace("\n", "\n  ")
                elif b_type == "callout":
                    child_md = "> " + child_md.replace("\n", "\n> ")
                content += child_md
                
            if b_type == "toggle":
                content += "\n</details>\n"
                
        return content

    except Exception as e:
        print(f"⚠️ 解析 Block 跳过 (Type: {block.get('type')}): {e}")
        return "" 

# ------------------------
# 自动清理功能 (核心修复)
# ------------------------
def clean_orphan_files(active_problem_numbers):
    if not os.path.exists(OUTPUT_DIR):
        return

    # 正则：匹配 "Leetcode Daily challenge-数字.md"
    pattern = re.compile(r"Leetcode Daily challenge-(\d+)\.md")
    
    print("-" * 30)
    print("🧹 正在清理旧文件...")
    
    files = os.listdir(OUTPUT_DIR)
    deleted_count = 0
    
    for filename in files:
        match = pattern.match(filename)
        if match:
            file_num = match.group(1)
            # 如果文件号不在本次解析到的 Notion 列表里 -> 删！
            if file_num not in active_problem_numbers:
                try:
                    os.remove(os.path.join(OUTPUT_DIR, filename))
                    print(f"🗑️ [已删除] 旧文件: {filename}")
                    deleted_count += 1
                except Exception as e:
                    print(f"❌ 删除失败 {filename}: {e}")
    
    if deleted_count == 0:
        print("✨ 没有需要清理的文件。")

# ------------------------
# 主逻辑
# ------------------------
def parse_notion_page():
    print(f"🔗 正在连接 Notion... (ID: {PAGE_ID[-4:]})")
    
    # 1. 递归抓取所有 Block
    all_root_blocks = get_block_children_recursive(PAGE_ID)
    
    if not all_root_blocks:
        print("❌ 未获取到任何内容")
        return

    print(f"🔍 成功获取 {len(all_root_blocks)} 个根 Block")

    current_title = None
    current_content = []
    all_files = []

    # 2. 解析内容
    for block in all_root_blocks:
        text = block_to_markdown(block) # 解析内容
        
        b_type = block["type"]
        plain_title = ""
        if "rich_text" in block.get(b_type, {}):
            plain_title = richtext_to_plain(block[b_type]["rich_text"])

        # 遇到一级标题 -> 切分新题目
        if b_type == "heading_1":
            if current_title:
                all_files.append((current_title, "".join(current_content)))
            
            current_title = plain_title if plain_title.strip() else "Untitled"
            current_content = []
            print(f"  👉 发现题目: {current_title}")
        else:
            # 其他内容归入当前题目
            current_content.append(text)

    # 保存最后一题
    if current_title:
        all_files.append((current_title, "".join(current_content)))

    # 3. 写入文件并记录有效题号
    active_problem_numbers = set()

    print("-" * 30)
    for title, content in all_files:
        # 提取题号 (兼容你的格式 1015. xxx)
        match = re.search(r"(\d{1,5})", title) 
        problem_number = match.group(1) if match else None
        
        if problem_number:
            active_problem_numbers.add(problem_number)
            file_path = os.path.join(OUTPUT_DIR, f"Leetcode Daily challenge-{problem_number}.md")
            os.makedirs(os.path.dirname(file_path), exist_ok=True)
            
            full_content = f"# {title}\n\n{content}"
            
            # 写入逻辑
            is_new = not os.path.exists(file_path)
            has_changed = False
            if not is_new:
                with open(file_path, "r", encoding="utf-8") as f:
                    if f.read().strip() != full_content.strip():
                        has_changed = True
            
            if is_new or has_changed:
                with open(file_path, "w", encoding="utf-8") as f:
                    f.write(full_content)
                status = "新增" if is_new else "更新"
                print(f"✅ [GitHub] {status}: {file_path}")
                if is_new: push_to_csdn(title, full_content)
            else:
                print(f"⏩ [GitHub] 无变化: {title}")
        else:
            print(f"⚠️ 跳过无题号内容: {title[:10]}...")

    # 4. 执行清理 (这一步现在一定能执行到了！)
    if active_problem_numbers:
        clean_orphan_files(active_problem_numbers)
    else:
        print("⚠️ 未解析到有效题号，跳过清理。")

if __name__ == "__main__":
    parse_notion_page()
