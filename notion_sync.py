import os
import re
import sys
from notion_client import Client

# ------------------------
# 配置：从环境变量读取 GitHub Secrets
# ------------------------
# 之前的写法（错误，会被写死的字符串覆盖）：
# NOTION_API_KEY = "YOUR_NOTION_API_KEY"
# PAGE_ID = "YOUR_PAGE_ID"

# ✅ 正确写法：从环境变量读取
NOTION_API_KEY = os.environ.get("NOTION_TOKEN")
PAGE_ID = os.environ.get("NOTION_PAGE_ID")

# 检查是否成功读取（调试用）
if not NOTION_API_KEY or not PAGE_ID:
    print("错误：无法读取环境变量 NOTION_TOKEN 或 NOTION_PAGE_ID")
    print("请检查 .github/workflows/notion-sync.yml 中的 env 配置是否正确")
    sys.exit(1)

notion = Client(auth=NOTION_API_KEY)


# 提取 Notion 页面所有 blocks
def get_all_blocks(block_id):
    blocks = []
    cursor = None

    while True:
        try:
            response = notion.blocks.children.list(block_id, start_cursor=cursor)
            blocks.extend(response.get("results"))
            if not response.get("has_more"):
                break
            cursor = response.get("next_cursor")
        except Exception as e:
            print(f"获取 Block 失败: {e}")
            break

    return blocks


# 提取题号：返回 1015
def extract_problem_number(title: str):
    match = re.search(r"(\d{1,5})", title)
    return match.group(1) if match else None


# 归档路径：Daily-Challenge
def generate_filepath(problem_number, title):
    folder = "LeetCode/Daily-Challenge"
    os.makedirs(folder, exist_ok=True)

    cleaned_title = re.sub(r'[\\/*?:"<>|]', "", title)
    filename = f"Leetcode Daily challenge-{problem_number}.md"

    return os.path.join(folder, filename)


# 读取 Notion 富文本内容（纯 markdown）
def richtext_to_md(rich):
    if not rich:
        return ""
    return "".join([x.get("plain_text", "") for x in rich])


# 主逻辑：解析 H1 → 生成多个 LeetCode 文件
def parse_notion_page():
    print(f"正在连接 Notion 页面 ID: {PAGE_ID} ...")
    blocks = get_all_blocks(PAGE_ID)
    
    if not blocks:
        print("警告：未获取到任何 Block，可能是 Page ID 错误或页面为空。")
        return

    current_title = None
    current_content = []

    all_files = []

    for block in blocks:
        block_type = block["type"]

        # 发现一级标题 = 新题目开始
        if block_type == "heading_1":
            # 如果之前有积累内容 → 写入文件
            if current_title:
                all_files.append((current_title, "\n".join(current_content)))

            # 安全获取标题文本
            rich_text = block[block_type].get("rich_text", [])
            if rich_text:
                current_title = rich_text[0]["plain_text"]
            else:
                current_title = "Untitled"
            
            current_content = []

        # 普通段落
        elif block_type == "paragraph":
            md = richtext_to_md(block["paragraph"]["rich_text"])
            current_content.append(md)

        # 代码块
        elif block_type == "code":
            lang = block["code"].get("language", "")
            code_text = "".join([x["plain_text"] for x in block["code"]["rich_text"]])
            current_content.append(f"\n```{lang}\n{code_text}\n```\n")
        
        # 列表项 (bulleted_list_item)
        elif block_type == "bulleted_list_item":
            md = richtext_to_md(block["bulleted_list_item"]["rich_text"])
            current_content.append(f"- {md}")

        # 数字列表 (numbered_list_item)
        elif block_type == "numbered_list_item":
            md = richtext_to_md(block["numbered_list_item"]["rich_text"])
            current_content.append(f"1. {md}")
            
        # 引用 (quote)
        elif block_type == "quote":
            md = richtext_to_md(block["quote"]["rich_text"])
            current_content.append(f"> {md}")

    # 最后一题写入
    if current_title:
        all_files.append((current_title, "\n".join(current_content)))

    # 写文件
    for title, content in all_files:
        problem_number = extract_problem_number(title)

        if problem_number:
            file_path = generate_filepath(problem_number, title)
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(f"# {title}\n\n{content}")
            print(f"成功生成: {file_path}")
        else:
            print(f"跳过（未识别题号）: {title}")


if __name__ == "__main__":
    parse_notion_page()
