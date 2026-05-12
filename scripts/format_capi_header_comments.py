#!/usr/bin/env python3
"""Conservatively move long C API declaration line comments to block comments.

This script is intentionally mechanical:
- It only rewrites single-line declarations that contain `; //`.
- It never changes the declaration text.
- It does not infer or normalize ownership semantics.
- It skips comments containing block-comment tokens.

Use `--dry-run` first, then `--apply` only after reviewing the candidate list.
"""

from __future__ import annotations

import argparse
from pathlib import Path
import re
from typing import Iterable


SAFETY_KEYWORDS = (
    "caller-owned",
    "borrowed",
    "invalid input",
    "factory failure",
    "may be NULL",
    "optional",
    "not retained",
    "rowBytes",
    "callback",
    "context",
    "NULL",
    "no-op",
    "returns 0",
    "returns false",
    "storage",
    "lifetime",
    "owned",
    "non-null",
    "must be valid",
    "required",
)

DECL_RE = re.compile(r"^(?P<indent>\s*)(?P<decl>[^/\n].*;\s*)//\s*(?P<comment>.*)$")


def iter_header_files(paths: Iterable[str], all_capi: bool) -> list[Path]:
    if all_capi:
        return sorted(Path("skia/capi").glob("*.h"))
    return [Path(path) for path in paths]


def is_pure_signature(comment: str) -> bool:
    stripped = comment.strip()
    return stripped.startswith("(") and ("->" in stripped or stripped.endswith(")"))


def is_candidate(comment: str, line: str, mode: str, min_length: int) -> bool:
    if "/*" in comment or "*/" in comment:
        return False
    if is_pure_signature(comment):
        return False
    has_keyword = any(keyword in comment for keyword in SAFETY_KEYWORDS)
    has_multiple_clauses = "; " in comment
    is_long = len(line.rstrip("\n")) >= min_length
    if mode == "strict":
        return has_keyword and (has_multiple_clauses or is_long)
    if mode == "moderate":
        return has_keyword or (has_multiple_clauses and is_long)
    raise ValueError(f"unknown mode: {mode}")


def split_comment(comment: str) -> list[str]:
    # Preserve wording while avoiding very long block-comment lines where the
    # original comment already used semicolon-separated safety clauses.
    parts = [part.strip() for part in comment.strip().split(";")]
    parts = [part for part in parts if part]
    if len(parts) <= 1:
        return [comment.strip()]
    lines: list[str] = []
    for index, part in enumerate(parts):
        suffix = "." if not part.endswith((".", ")", "`")) else ""
        # Keep trailing Skia signature fragments visually distinct but do not
        # attempt to parse nested function-pointer signatures.
        lines.append(f"{part}{suffix}")
    return lines


def convert_line(line: str, mode: str, min_length: int) -> tuple[bool, list[str]]:
    match = DECL_RE.match(line)
    if not match:
        return False, [line]
    indent = match.group("indent")
    decl = match.group("decl").rstrip()
    comment = match.group("comment")
    if not is_candidate(comment, line, mode, min_length):
        return False, [line]
    block = [f"{indent}/**\n"]
    for comment_line in split_comment(comment):
        block.append(f"{indent} * {comment_line}\n")
    block.append(f"{indent} */\n")
    block.append(f"{indent}{decl}\n")
    return True, block


def process_file(path: Path, mode: str, min_length: int, apply: bool) -> int:
    original = path.read_text(encoding="utf-8").splitlines(keepends=True)
    changed = 0
    output: list[str] = []
    for line in original:
        did_change, new_lines = convert_line(line, mode, min_length)
        if did_change:
            changed += 1
        output.extend(new_lines)
    if apply and changed:
        path.write_text("".join(output), encoding="utf-8")
    return changed


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("paths", nargs="*", help="Header files to process")
    parser.add_argument("--all-capi", action="store_true", help="Process all skia/capi/*.h")
    parser.add_argument("--mode", choices=("strict", "moderate"), default="strict")
    parser.add_argument("--min-length", type=int, default=140)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--dry-run", action="store_true")
    group.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    files = iter_header_files(args.paths, args.all_capi)
    total = 0
    for path in files:
        if not path.exists():
            raise FileNotFoundError(path)
        changed = process_file(path, args.mode, args.min_length, args.apply)
        if changed:
            print(f"{path}: {changed}")
            total += changed
    print(f"total: {total}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
