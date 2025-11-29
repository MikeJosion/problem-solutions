#!/usr/bin/env python3
import os

DAILY_DIR = "LeetCode/Daily-Challenge"
TOC_FILE = f"{DAILY_DIR}/README.md"

def generate_toc():
    files = sorted(
        f for f in os.listdir(DAILY_DIR)
        if f.endswith(".md") and f != "README.md"
    )

    lines = ["# Daily Challenge TOC\n"]

    for filename in files:
        title = filename.replace(".md", "")
        lines.append(f"- [{title}]({filename})")

    with open(TOC_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

if __name__ == "__main__":
    generate_toc()
    print("TOC generated successfully!")
