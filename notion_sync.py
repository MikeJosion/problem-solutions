{"id":"58102","variant":"standard","title":"notion_sync.py 完整版"}
import os
import re
from notion_client import Client

# ------------------------
# 配置：请填写你的 Notion API KEY 和 PAGE ID
# ------------------------
NOTION_API_KEY = "YOUR_NOTION_API_KEY"
PAGE_ID = "YOUR_PAGE_ID"

notion = Client(auth=NOTION_API_KEY)


# 提取 Notion 页面所有 blocks
def get_all_blocks(block_id):
    blocks = []
    cursor = None

    while True:
        response = notion.blocks.children.list(block_id, start_cursor=cursor)
        blocks.extend(response.get("results"))
        if not response.get("has_more"):
            break
        cursor = response.get("next_cursor")

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
    blocks = get_all_blocks(PAGE_ID)

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

            current_title = block[block_type]["rich_text"][0]["plain_text"]
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

        # 其它 block 可自行扩展（列表、引用等）

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
            print("生成:", file_path)
        else:
            print("跳过（未识别题号）:", title)


if __name__ == "__main__":
    parse_notion_page()
