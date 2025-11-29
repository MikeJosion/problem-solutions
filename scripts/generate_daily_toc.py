import os
import re

BASE_DIR = "LeetCode/Daily-Challenge"
README_PATH = os.path.join(BASE_DIR, "README.md")

def generate_table():
rows = []

```
for filename in sorted(os.listdir(BASE_DIR)):
    if filename.endswith(".md") and filename != "README.md":
        # 提取日期
        match = re.search(r"(\d{4}-?\d{2}-?\d{2})", filename)
        date_str = match.group(1) if match else "未知日期"

        # 修正日期格式：20251015 → 2025-10-15
        if "-" not in date_str and len(date_str) == 8:
            date_str = f"{date_str[:4]}-{date_str[4:6]}-{date_str[6:8]}"

        # 文件名转 URL
        file_url = filename.replace(" ", "%20")

        # 去掉 .md 后缀
        title = filename.replace(".md", "")

        rows.append(f"| {date_str} | {title} | [查看](./{file_url}) |")

return "\n".join(rows)
```

def generate_readme():
header = """# 🌟 LeetCode Daily Challenge 目录

自动生成的题解目录（每次 Push 自动更新）

---

| 日期  | 题目 | 链接 |
| --- | -- | -- |
| """ |    |    |

```
table = generate_table()

with open(README_PATH, "w", encoding="utf-8") as f:
    f.write(header + table)

print("📘 Daily-Challenge TOC 生成完毕！")
```

if **name** == "**main**":
generate_readme()
