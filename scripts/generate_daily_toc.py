#!/usr/bin/env python3
import os

DAILY_DIR = "LeetCode/Daily-Challenge"
TOC_FILE = f"{DAILY_DIR}/README.md"

def generate_toc():
    # 1. 安全检查：如果文件夹不存在，先创建它，防止报错
    if not os.path.exists(DAILY_DIR):
        os.makedirs(DAILY_DIR)
        print(f"目录 {DAILY_DIR} 不存在，已自动创建。")
        return  # 文件夹刚创建肯定是空的，直接结束

    # 2. 获取所有 .md 文件
    files = sorted(
        f for f in os.listdir(DAILY_DIR)
        if f.endswith(".md") and f != "README.md"
    )

    if not files:
        print("没有找到 .md 文件，跳过生成目录。")
        return

    # 3. 生成目录内容
    lines = ["# Daily Challenge TOC\n"]
    for filename in files:
        title = filename.replace(".md", "")
        # 使用 URL 编码处理文件名中的空格，防止链接失效
        safe_link = filename.replace(" ", "%20")
        lines.append(f"- [{title}]({safe_link})")

    # 4. 写入文件
    with open(TOC_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    
    print(f"成功更新目录，共包含 {len(files)} 个题目。")

if __name__ == "__main__":
    generate_toc()
