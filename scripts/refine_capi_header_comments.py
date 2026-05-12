#!/usr/bin/env python3
"""Refine already-blockified C API header comments.

This is a second, narrower pass after format_capi_header_comments.py:
- It only edits lines inside existing /** ... */ comments.
- It never changes declarations or preprocessor lines.
- It separates trailing Skia signature fragments into a dedicated `Skia:`
  line so safety text remains readable.
- It applies a small set of exact wording normalizations used by the current
  high-touch C API headers.

Use --dry-run first and review the diff before --apply.
"""

from __future__ import annotations

import argparse
from pathlib import Path
from typing import Iterable


DEFAULT_FILES = (
    "skia/capi/sk_canvas.h",
    "skia/capi/sk_image.h",
    "skia/capi/sk_runtime_effect.h",
    "skia/capi/sk_runtime_shader_builder.h",
    "skia/capi/sk_runtime_color_filter_builder.h",
    "skia/capi/sk_runtime_blend_builder.h",
    "skia/capi/sk_runtime_effect_builder.h",
)


EXACT_REPLACEMENTS = {
    "borrowed: 解放不要の借用ポインタ": "Borrowed pointer; caller must not free.",
    "borrowed: 解放不要の借用ポインタ。runtime_effect/name must be valid.": (
        "Borrowed pointer; caller must not free. runtime_effect/name must be valid."
    ),
    "owned: caller が保持する参照を release する。NULL runtime_effect は no-op": (
        "Releases the caller-held reference. NULL runtime_effect is no-op."
    ),
    "owned: caller が保持する参照を release する": (
        "Releases the caller-held reference."
    ),
    "retained: 参照カウントを増やす。NULL runtime_effect は no-op": (
        "Retains runtime_effect. NULL runtime_effect is no-op."
    ),
    "owned: 参照カウントを減らす。NULL runtime_effect は no-op": (
        "Releases runtime_effect. NULL runtime_effect is no-op."
    ),
    "owned: 参照カウントを減らす": "Releases the reference.",
    "invalid runtime_effect handle なら NULL": (
        "Invalid runtime_effect handle returns NULL."
    ),
    "NULL builder なら NULL": "NULL builder returns NULL.",
    "NULL builder なら 0": "NULL builder returns 0.",
    "NULL builder は no-op": "NULL builder is no-op.",
    "NULL runtime_effect なら NULL": "NULL runtime_effect returns NULL.",
    "NULL runtime_effect なら 0": "NULL runtime_effect returns 0.",
    "NULL runtime_effect なら false": "NULL runtime_effect returns false.",
    "invalid picture handle は no-op。matrix/paint may be NULL": (
        "Invalid picture handle is no-op. matrix/paint may be NULL."
    ),
    "invalid picture handle は no-op": "Invalid picture handle is no-op.",
    "生成不能なら 0": "factory failure returns 0",
    "生成不能なら": "factory failure returns",
}


PREFIX_REPLACEMENTS = (
    ("invalid input", "Invalid input"),
    ("returns 0 on", "Returns 0 on"),
    ("returned trace handle is caller-owned", "Returns a caller-owned trace handle"),
    ("returned shader handle is caller-owned", "Returns a caller-owned shader handle"),
    ("returned ", "Returned "),
    ("caller must", "Caller must"),
    ("caller deletes", "Caller deletes"),
    ("borrowed ", "Borrowed "),
    ("pointer is", "Pointer is"),
    ("non-zero", "Non-zero"),
    ("children is non-null", "children must be non-null"),
)

SKIA_WRAP_LIMIT = 140


def iter_files(paths: Iterable[str], default_set: bool) -> list[Path]:
    if default_set:
        return [Path(path) for path in DEFAULT_FILES]
    return [Path(path) for path in paths]


def ensure_sentence(text: str) -> str:
    text = text.strip()
    if not text:
        return text
    if text.endswith((".", ")", "`")):
        return text
    return f"{text}."


def normalize_text(text: str) -> str:
    text = text.strip()
    for old, new in EXACT_REPLACEMENTS.items():
        text = text.replace(old, new)
    text = text.replace(".。", ".").replace("。", " ")
    while ".." in text:
        text = text.replace("..", ".")
    text = text.replace(".NULL", ". NULL")
    text = text.replace(".runtime_effect", ". runtime_effect")
    text = text.replace(".matrix", ". matrix")
    for old, new in PREFIX_REPLACEMENTS:
        if text.startswith(old):
            text = f"{new}{text[len(old):]}"
    return ensure_sentence(text)


def split_signature_fragment(text: str) -> list[str]:
    if text == "Skia:":
        return [text]
    if text.startswith("Skia:"):
        return [normalize_text(text)]
    if text.startswith("("):
        return [normalize_text(text)]

    marker = " ("
    split_at = text.find(marker)
    if split_at == -1:
        return [normalize_text(text)]

    safety_text = text[:split_at].strip()
    signature = text[split_at + 1 :].strip().rstrip(".")
    if not safety_text or not signature.startswith("("):
        return [normalize_text(text)]
    if " -> " not in signature and "Sk" not in signature and "sk_" not in signature:
        return [normalize_text(text)]
    return [normalize_text(safety_text), f"Skia: {signature}."]


def wrap_skia_signature(text: str) -> list[str]:
    if not text.startswith("Skia: (") or len(text) <= SKIA_WRAP_LIMIT:
        return [text]

    signature = text[len("Skia: ") :].rstrip(".")
    returns = ""
    if " -> " in signature:
        signature, returns = signature.split(" -> ", 1)
    if not signature.startswith("(") or not signature.endswith(")"):
        return [text]

    args = [arg.strip() for arg in signature[1:-1].split(", ")]
    if len(args) <= 1:
        return [text]

    lines = ["Skia:"]
    for index, arg in enumerate(args):
        prefix = "(" if index == 0 else " "
        is_last = index == len(args) - 1
        if is_last and returns:
            suffix = f") -> {returns}."
        elif is_last:
            suffix = ")."
        else:
            suffix = ","
        lines.append(f"  {prefix}{arg}{suffix}")
    return lines


def convert_comment_line(line: str) -> tuple[bool, list[str]]:
    stripped = line.lstrip()
    indent = line[: len(line) - len(stripped)]
    if not stripped.startswith("* "):
        return False, [line]
    content = stripped[2:].rstrip("\n")
    if content.startswith("  "):
        return False, [line]
    refined: list[str] = []
    for item in split_signature_fragment(content):
        refined.extend(wrap_skia_signature(item))
    new_lines = [f"{indent}* {item}\n" for item in refined]
    return new_lines != [line], new_lines


def process_file(path: Path, apply: bool) -> int:
    original = path.read_text(encoding="utf-8").splitlines(keepends=True)
    output: list[str] = []
    in_block = False
    changes = 0

    for line in original:
        stripped = line.lstrip()
        if stripped.startswith("/**"):
            in_block = True
            output.append(line)
            continue
        if in_block and stripped.startswith("*/"):
            in_block = False
            output.append(line)
            continue
        if in_block:
            changed, new_lines = convert_comment_line(line)
            if changed:
                changes += 1
            output.extend(new_lines)
            continue
        output.append(line)

    if apply and changes:
        path.write_text("".join(output), encoding="utf-8")
    return changes


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("paths", nargs="*", help="Header files to process")
    parser.add_argument(
        "--default-set",
        action="store_true",
        help="Process the high-touch C API headers selected for comment refinement",
    )
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--dry-run", action="store_true")
    group.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    files = iter_files(args.paths, args.default_set)
    if not files:
        parser.error("provide paths or --default-set")

    total = 0
    for path in files:
        if not path.exists():
            raise FileNotFoundError(path)
        changed = process_file(path, args.apply)
        if changed:
            print(f"{path}: {changed}")
            total += changed
    print(f"total: {total}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
