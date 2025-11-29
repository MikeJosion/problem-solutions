import os
import requests
from slugify import slugify

NOTION_TOKEN = os.environ["NOTION_TOKEN"]
PAGE_ID = os.environ["NOTION_PAGE_ID"]

headers = {
    "Authorization": f"Bearer {NOTION_TOKEN}",
    "Notion-Version": "2022-06-28"
}

def fetch_blocks(page_id):
    url = f"https://api.notion.com/v1/blocks/{page_id}/children?page_size=100"
    response = requests.get(url, headers=headers).json()
    return response.get("results", [])

def extract_text(block):
    """取 block 中所有 text 内容"""
    try:
        return "".join(r["plain_text"] for r in block["paragraph"]["rich_text"])
    except:
        return ""

def extract_heading(block):
    try:
        return "".join(r["plain_text"] for r in block["heading_1"]["rich_text"])
    except:
        return None

def get_leetcode_number(title):
    """从标题提取题号，如 'Leetcode 1015 - xxx' → 1015"""
    import re
    match = re.search(r"(\d+)", title)
    return match.group(1) if match else None

def save_file(title, content):
    """根据标题分类保存文件"""

    problem_number = get_leetcode_number(title)

    if problem_number:
        folder = "LeetCode/Daily-Challenge"
        os.makedirs(folder, exist_ok=True)
        filename = f"Leetcode Daily challenge-{problem_number}.md"
    else:
        folder = "Notes"
        os.makedirs(folder, exist_ok=True)
        filename = f"{slugify(title)}.md"

    filepath = f"{folder}/{filename}"

    with open(filepath, "w", encoding="utf-8") as f:
        f.write(f"# {title}\n\n")
        f.write(content)

    print("Saved:", filepath)


def main():
    blocks = fetch_blocks(PAGE_ID)

    page_title = "Untitled"
    content = ""

    for block in blocks:
        # 一级标题
        h = extract_heading(block)
        if h:
            page_title = h
            continue

        # 段落
        text = extract_text(block)
        if text.strip():
            content += text + "\n\n"

    save_file(page_title, content)


if __name__ == "__main__":
    main()
