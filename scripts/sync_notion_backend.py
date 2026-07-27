"""Sync a Notion page tree into BackendEngineering as Markdown files."""

from __future__ import annotations

import os
import re
import sys
from pathlib import Path

from notion_client import Client


TOKEN = os.environ.get("NOTION_TOKEN", "").strip()
ROOT_PAGE_ID = os.environ.get("NOTION_BACKEND_PAGE_ID", "").strip()
OUTPUT_DIR = Path(os.environ.get("NOTION_BACKEND_OUTPUT_DIR", "BackendEngineering"))


def rich_text(items: list[dict]) -> str:
    parts: list[str] = []
    for item in items:
        text = item.get("plain_text", "")
        if item.get("type") == "equation":
            text = f"${item.get('equation', {}).get('expression', text)}$"
        elif item.get("href"):
            text = f"[{text}]({item['href']})"
        else:
            annotations = item.get("annotations", {})
            if annotations.get("code"):
                text = f"`{text}`"
            if annotations.get("bold"):
                text = f"**{text}**"
            if annotations.get("italic"):
                text = f"*{text}*"
            if annotations.get("strikethrough"):
                text = f"~~{text}~~"
        parts.append(text)
    return "".join(parts)


def safe_name(value: str) -> str:
    value = re.sub(r'[<>:"/\\|?*\x00-\x1f]', "-", value).strip().rstrip(".")
    return value[:120] or "Untitled"


def children(client: Client, block_id: str) -> list[dict]:
    result: list[dict] = []
    cursor = None
    while True:
        response = client.blocks.children.list(
            block_id=block_id, start_cursor=cursor, page_size=100
        )
        result.extend(response["results"])
        if not response.get("has_more"):
            return result
        cursor = response.get("next_cursor")


def block_markdown(client: Client, block: dict, depth: int = 0) -> str:
    block_type = block.get("type", "")
    data = block.get(block_type, {})
    text = rich_text(data.get("rich_text", []))

    renderers = {
        "paragraph": lambda: f"{text}\n\n",
        "heading_1": lambda: f"# {text}\n\n",
        "heading_2": lambda: f"## {text}\n\n",
        "heading_3": lambda: f"### {text}\n\n",
        "bulleted_list_item": lambda: f"{'  ' * depth}- {text}\n",
        "numbered_list_item": lambda: f"{'  ' * depth}1. {text}\n",
        "to_do": lambda: f"- [{'x' if data.get('checked') else ' '}] {text}\n",
        "quote": lambda: f"> {text}\n\n",
        "callout": lambda: f"> {text}\n\n",
        "code": lambda: (
            f"```{data.get('language', '')}\n{text}\n```\n\n"
        ),
        "equation": lambda: f"$$\n{data.get('expression', '')}\n$$\n\n",
        "divider": lambda: "---\n\n",
        "bookmark": lambda: f"<{data.get('url', '')}>\n\n",
        "image": lambda: (
            f"![{data.get('caption', [{}])[0].get('plain_text', '') if data.get('caption') else ''}]"
            f"({data.get(data.get('type', ''), {}).get('url', '')})\n\n"
        ),
    }
    rendered = renderers.get(block_type, lambda: "")()

    if block.get("has_children") and block_type not in {"child_page", "child_database"}:
        nested = "".join(
            block_markdown(client, child, depth + 1)
            for child in children(client, block["id"])
        )
        rendered += nested
        if block_type in {"bulleted_list_item", "numbered_list_item"}:
            rendered += "\n"
    return rendered


def page_title(client: Client, page_id: str) -> str:
    page = client.pages.retrieve(page_id=page_id)
    for prop in page.get("properties", {}).values():
        if prop.get("type") == "title":
            return rich_text(prop.get("title", [])) or "Untitled"
    return "Untitled"


def write_if_changed(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    normalized = content.rstrip() + "\n"
    if path.exists() and path.read_text(encoding="utf-8") == normalized:
        print(f"unchanged: {path}")
        return
    path.write_text(normalized, encoding="utf-8")
    print(f"updated:   {path}")


def sync_page(client: Client, page_id: str, destination: Path, is_root: bool) -> None:
    title = page_title(client, page_id)
    blocks = children(client, page_id)
    content = [f"# {title}\n\n"]
    child_pages: list[dict] = []

    for block in blocks:
        if block.get("type") == "child_page":
            child_pages.append(block)
            child_title = block["child_page"].get("title", "Untitled")
            content.append(f"- [{child_title}](./{safe_name(child_title)}/README.md)\n")
        else:
            content.append(block_markdown(client, block))

    write_if_changed(destination / "README.md", "".join(content))
    for child in child_pages:
        child_title = child["child_page"].get("title", "Untitled")
        sync_page(client, child["id"], destination / safe_name(child_title), False)


def main() -> None:
    if not TOKEN or not ROOT_PAGE_ID:
        print("NOTION_TOKEN and NOTION_BACKEND_PAGE_ID are required.", file=sys.stderr)
        raise SystemExit(1)
    sync_page(Client(auth=TOKEN), ROOT_PAGE_ID, OUTPUT_DIR, True)


if __name__ == "__main__":
    main()
