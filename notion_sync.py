import os
import re
import sys
from notion_client import Client

# ------------------------
# 配置：从环境变量读取 GitHub Secrets
# ------------------------
# ✅ 修复重点：添加 .strip() 自动去除多余的空格和换行符
NOTION_API_KEY = os.environ.get("NOTION_TOKEN", "").strip()
PAGE_ID = os.environ.get("NOTION_PAGE_ID", "").strip()

if not NOTION_API_KEY or not PAGE_ID:
    print("❌ 错误：无法读取环境变量，请检查 GitHub Secrets 配置")
    sys.exit(1)

notion = Client(auth=NOTION_API_KEY)

def get_all_blocks(block_id):
    blocks = []
    cursor = None
    while True:
        try:
            # 去除可能存在的连字符，防止 ID 格式不兼容
            safe_block_id = block_id.replace("-", "")
            response = notion.blocks.children.list(safe_block_id, start_cursor=cursor)
            blocks.extend(response.get("results"))
            if not response.get("has_more"):
                break
            cursor = response.get("next_cursor")
        except Exception as e:
            print(f"❌ 获取 Block 失败: {e}")
            # 打印 ID 长度帮助调试
            print(f"   (调试信息: 使用的 Page ID 长度为 {len(block_id)}，内容: '{block_id}')")
            break
    return blocks

def extract_problem_number(title: str):
    match = re.search(r"(\d{1,5})", title)
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
    return "".join([x.get("plain_text", "") for x in rich_text_list])

def parse_notion_page():
    print(f"🔗 正在连接 Notion 页面 ID: {PAGE_ID[:4]}***{PAGE_ID[-4:]} (已去除空格)")
    blocks = get_all_blocks(PAGE_ID)
    
    if not blocks:
        print("❌ 警告：未获取到任何 Block。")
        return

    print(f"🔍 成功获取到 {len(blocks)} 个 Block，开始解析...")

    current_title = None
    current_content = []
    all_files = []

    for i, block in enumerate(blocks):
        block_type = block["type"]
        
        # 获取预览文本
        preview_text = ""
        if "rich_text" in block.get(block_type, {}):
            preview_text = richtext_to_plain(block[block_type]["rich_text"])
        
        # 调试打印
        # print(f"Block {i+1} [{block_type}]: {preview_text[:30]}...") 

        if block_type == "heading_1":
            if current_title:
                all_files.append((current_title, "\n".join(current_content)))

            current_title = preview_text
            if not current_title.strip():
                current_title = "Untitled"
            
            current_content = []
            print(f"  👉 发现新题目: {current_title}")

        elif block_type == "paragraph":
            current_content.append(preview_text)
        elif block_type == "code":
            lang = block["code"].get("language", "text")
            code_text = preview_text
            current_content.append(f"\n```{lang}\n{code_text}\n```\n")
        elif block_type == "bulleted_list_item":
            current_content.append(f"- {preview_text}")
        elif block_type == "numbered_list_item":
            current_content.append(f"1. {preview_text}")
        elif block_type == "quote":
            current_content.append(f"> {preview_text}")
        elif block_type == "callout":
            current_content.append(f"> 💡 **Note:**\n> {preview_text}")

    if current_title:
        all_files.append((current_title, "\n".join(current_content)))

    print("-" * 30)
    for title, content in all_files:
        problem_number = extract_problem_number(title)
        if problem_number:
            file_path = generate_filepath(problem_number, title)
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(f"# {title}\n\n{content}")
            print(f"✅ 生成文件: {file_path}")
        else:
            print(f"⚠️ 跳过（标题没数字）: {title}")

if __name__ == "__main__":
    parse_notion_page()
