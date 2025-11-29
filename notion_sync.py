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

if not NOTION_API_KEY or not PAGE_ID:
    print("❌ 错误：无法读取 NOTION_TOKEN 或 NOTION_PAGE_ID")
    sys.exit(1)

notion = Client(auth=NOTION_API_KEY)

# ------------------------
# CSDN 发布功能模块
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
# Notion 解析逻辑 (升级版)
# ------------------------
def get_all_blocks(block_id):
    blocks = []
    cursor = None
    while True:
        try:
            safe_block_id = block_id.replace("-", "")
            response = notion.blocks.children.list(safe_block_id, start_cursor=cursor)
            blocks.extend(response.get("results"))
            if not response.get("has_more"):
                break
            cursor = response.get("next_cursor")
        except Exception as e:
            print(f"❌ 获取 Block 失败: {e}")
            break
    return blocks

def extract_problem_number(title: str):
    # 只认开头是数字的标题
    match = re.search(r"^(\d{1,5})", title.strip())
    return match.group(1) if match else None

def generate_filepath(problem_number, title):
    folder = "LeetCode/Daily-Challenge"
    os.makedirs(folder, exist_ok=True)
    cleaned_title = re.sub(r'[\\/*?:"<>|]', "", title).strip()
    filename = f"Leetcode Daily challenge-{problem_number}.md"
    return os.path.join(folder, filename)

def richtext_to_plain(rich_text_list):
    if not rich_text_list:
        return ""
    # 这里可以扩展：处理加粗、斜体、行内公式等
    text_content = ""
    for x in rich_text_list:
        plain = x.get("plain_text", "")
        # 如果是行内公式 (Inline Equation)
        if x.get("type") == "equation":
            plain = f"${plain}$"  # 包裹 LaTeX 符号
        text_content += plain
    return text_content

def parse_notion_page():
    print(f"🔗 连接 Notion 页面: {PAGE_ID[:4]}...{PAGE_ID[-4:]}")
    blocks = get_all_blocks(PAGE_ID)
    
    if not blocks:
        print("❌ 未获取到内容")
        return

    print(f"🔍 获取到 {len(blocks)} 个 Block")

    current_title = None
    current_content = []
    all_files = []

    for block in blocks:
        block_type = block["type"]
        
        # 获取纯文本内容的通用方法 (针对有 rich_text 的块)
        preview_text = ""
        if "rich_text" in block.get(block_type, {}):
            preview_text = richtext_to_plain(block[block_type]["rich_text"])

        # --- 识别逻辑 ---

        # 1. 题目开始 (一级标题)
        if block_type == "heading_1":
            if current_title:
                all_files.append((current_title, "\n".join(current_content)))

            current_title = preview_text
            if not current_title.strip():
                current_title = "Untitled"
            current_content = []
            print(f"  👉 识别题目: {current_title}")

        # 2. 也是标题，但归入正文 (二级、三级标题)
        elif block_type == "heading_2":
            current_content.append(f"\n## {preview_text}\n")
        elif block_type == "heading_3":
            current_content.append(f"\n### {preview_text}\n")

        # 3. 基础文本
        elif block_type == "paragraph":
            if preview_text.strip(): # 只有不为空才添加，避免过多空行
                current_content.append(preview_text)
            else:
                current_content.append("") # 保留段落间的空行

        # 4. 代码块
        elif block_type == "code":
            lang = block["code"].get("language", "text")
            code_text = preview_text
            current_content.append(f"\n```{lang}\n{code_text}\n```\n")

        # 5. 独立公式块 (Block Equation) - 你的笔记里有很多这个
        elif block_type == "equation":
            expression = block["equation"].get("expression", "")
            # 转换为 Markdown 的 LaTeX 格式
            current_content.append(f"\n$$\n{expression}\n$$\n")

        # 6. 列表和引用
        elif block_type == "bulleted_list_item":
            current_content.append(f"- {preview_text}")
        elif block_type == "numbered_list_item":
            current_content.append(f"1. {preview_text}")
        elif block_type == "quote":
            current_content.append(f"> {preview_text}")
        elif block_type == "callout":
            current_content.append(f"> 💡 **Note:**\n> {preview_text}")
        
        # 7. 待办事项 (To-Do)
        elif block_type == "to_do":
            checked = "x" if block["to_do"].get("checked") else " "
            current_content.append(f"- [{checked}] {preview_text}")
            
        # 8. 分割线
        elif block_type == "divider":
            current_content.append("\n---\n")

    # 保存最后一题
    if current_title:
        all_files.append((current_title, "\n".join(current_content)))

    # --- 写入与发布 ---
    print("-" * 30)
    for title, content in all_files:
        problem_number = extract_problem_number(title)
        if problem_number:
            file_path = generate_filepath(problem_number, title)
            full_content = f"# {title}\n\n{content}"
            
            is_new_file = not os.path.exists(file_path)
            
            # 检查变化（简单的全量比对）
            has_changed = False
            if not is_new_file:
                with open(file_path, "r", encoding="utf-8") as f:
                    old_content = f.read()
                # 忽略换行符差异
                if old_content.strip() != full_content.strip():
                    has_changed = True

            if is_new_file or has_changed:
                with open(file_path, "w", encoding="utf-8") as f:
                    f.write(full_content)
                
                if is_new_file:
                    print(f"✅ [GitHub] 新增: {file_path}")
                    push_to_csdn(title, full_content) 
                else:
                    print(f"✅ [GitHub] 更新: {file_path}")
                    # 如果你想让“内容更新”也同步到 CSDN，可以在这里取消注释 push_to_csdn
                    # 但注意：CSDN 接口没 ID 会重复发帖，除非你手动去 CSDN 删旧贴
                    # push_to_csdn(title, full_content) 
            else:
                print(f"⏩ [GitHub] 无变化: {title}")
        else:
            print(f"⚠️ 跳过（无题号）: {title}")

if __name__ == "__main__":
    parse_notion_page()
