#!/usr/bin/env python3
"""Generate a coarse public Skia API to Reskia C API coverage matrix.

This is intentionally heuristic. It uses the vendored public headers as the
source of truth, extracts top-level class/struct method declarations, and
matches them against Reskia C API function names.
"""

from __future__ import annotations

import argparse
import csv
import re
from dataclasses import dataclass
from pathlib import Path


API_MACROS = (
    "SK_API",
    "SK_SPI",
    "SKSHAPER_API",
    "SKSVG_API",
    "SKOTTIE_API",
    "SKSG_API",
    "SKUNICODE_API",
    "SKCMS_API",
    "SKSL_API",
    "SKPARAGRAPH_API",
    "SK_RESOURCES_API",
    "SK_TRIVIAL_ABI",
)


@dataclass(frozen=True)
class Method:
    name: str
    static: bool
    signature: str
    line: int


@dataclass(frozen=True)
class PublicClass:
    name: str
    kind: str
    path: str
    area: str
    line: int
    methods: tuple[Method, ...]


def area_for(rel: str) -> str:
    parts = rel.split("/")
    if rel.startswith("include/"):
        return "include/" + (parts[1] if len(parts) > 2 else "")
    if rel.startswith("modules/") and len(parts) > 1:
        return "modules/" + parts[1]
    return parts[0]


def snake(name: str) -> str:
    value = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", "_", name)
    value = re.sub(r"(?<=[A-Z])(?=[A-Z][a-z])", "_", value)
    return value.lower()


def public_header_paths(repo: Path) -> list[Path]:
    root = repo / "vendor/skia-upstream"
    roots = [root / "include"]
    modules = root / "modules"
    if modules.exists():
        roots.extend(sorted(p / "include" for p in modules.iterdir() if (p / "include").exists()))

    paths: list[Path] = []
    for base in roots:
        if not base.exists():
            continue
        for path in base.rglob("*"):
            if path.suffix not in (".h", ".hpp"):
                continue
            if "/include/private/" in str(path):
                continue
            if "/include/third_party/" in str(path):
                continue
            paths.append(path)
    return sorted(paths)


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//.*", "", text)
    text = re.sub(r"^\s*#.*$", "", text, flags=re.M)
    return text


def find_matching_brace(text: str, open_pos: int) -> int:
    depth = 0
    for pos in range(open_pos, len(text)):
        char = text[pos]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return pos
    return -1


def line_number(text: str, pos: int) -> int:
    return text.count("\n", 0, pos) + 1


def class_definitions(repo: Path, path: Path) -> list[tuple[str, str, str, int, str]]:
    root = repo / "vendor/skia-upstream"
    rel = str(path.relative_to(root))
    text = strip_comments(path.read_text(errors="ignore"))
    macros = "|".join(re.escape(m) for m in API_MACROS)
    pattern = re.compile(
        rf"\b(class|struct)\s+(?:(?:{macros})\s+)?([A-Za-z_][A-Za-z0-9_]*)\b[^;{{]*{{"
    )

    results: list[tuple[str, str, str, int, str]] = []
    occupied: list[tuple[int, int]] = []
    for match in pattern.finditer(text):
        start = match.start()
        if any(a < start < b for a, b in occupied):
            continue
        before = text[max(0, start - 200) : start]
        if re.search(r"template\s*<[^>{;]*>\s*$", before, flags=re.S):
            continue
        open_pos = text.find("{", match.start(), match.end())
        close_pos = find_matching_brace(text, open_pos)
        if close_pos < 0:
            continue
        occupied.append((open_pos, close_pos))
        kind = match.group(1)
        name = match.group(2)
        body = text[open_pos + 1 : close_pos]
        results.append((name, kind, rel, line_number(text, match.start()), body))
    return results


def split_top_level_statements(body: str) -> list[tuple[int, str]]:
    statements: list[tuple[int, str]] = []
    access = None
    current: list[str] = []
    start_line = 1
    depth_angle = 0
    depth_paren = 0
    depth_brace = 0
    line = 1
    token_line = 1

    for char in body:
        if not current and not char.isspace():
            token_line = line
        current.append(char)
        if char == "\n":
            line += 1
        elif char == "<":
            depth_angle += 1
        elif char == ">" and depth_angle:
            depth_angle -= 1
        elif char == "(":
            depth_paren += 1
        elif char == ")" and depth_paren:
            depth_paren -= 1
        elif char == "{":
            depth_brace += 1
        elif char == "}" and depth_brace:
            depth_brace -= 1

        if depth_angle == 0 and depth_paren == 0 and depth_brace == 0 and char in (";", "{", "}"):
            statement = "".join(current).strip()
            if statement:
                statements.append((token_line, statement))
            current = []
            start_line = line
    return statements


def normalize_statement(statement: str) -> str:
    statement = " ".join(statement.replace("\n", " ").split())
    statement = re.sub(r"\b(SK_API|SK_SPI|SK_WARN_UNUSED_RESULT|SK_ATTR_DEPRECATED)\b", "", statement)
    statement = re.sub(r"\[\[.*?\]\]", "", statement)
    return " ".join(statement.split())


def method_name(class_name: str, statement: str) -> str | None:
    s = normalize_statement(statement).rstrip(";{").strip()
    if not s or "(" not in s:
        return None
    if s.startswith(("using ", "typedef ", "friend ", "enum ", "class ", "struct ", "template ")):
        return None
    if s.startswith(("static_assert", "SK_DECL", "SK_FLATTENABLE")):
        return None
    if re.search(r"=\s*delete\b", s):
        return None
    if "=" in s.split("(", 1)[0] and "operator" not in s:
        return None

    before = s.split("(", 1)[0].strip()
    before = before.replace("~ ", "~")
    if not before:
        return None

    op = re.search(r"\boperator\s*([^\s(]+)", before)
    if op:
        op_name = "operator" + op.group(1)
        if op_name in {"operatornew", "operatordelete", "operatornew[]", "operatordelete[]", "operator="}:
            return None
        return op_name

    token = before.split()[-1]
    token = token.split("::")[-1]
    token = token.lstrip("*&")
    if token == "operator":
        return "operator()"
    if token.startswith(("SkDEBUGCODE", "SG_ATTRIBUTE")):
        return None
    if token in ("const", "volatile", "override", "final"):
        return None
    if token == class_name:
        return class_name
    if token == "~" + class_name:
        return "~" + class_name
    if re.match(r"^[A-Za-z_~][A-Za-z0-9_~]*$", token):
        return token
    return None


def extract_methods(class_name: str, kind: str, body: str, class_line: int) -> tuple[Method, ...]:
    default_public = kind == "struct"
    public = default_public
    methods: list[Method] = []

    for rel_line, statement in split_top_level_statements(body):
        compact = normalize_statement(statement)
        if compact in ("public:", "protected:", "private:"):
            public = compact == "public:"
            continue
        if compact.startswith("public:"):
            public = True
            compact = compact[len("public:") :].strip()
        elif compact.startswith("protected:"):
            public = False
            compact = compact[len("protected:") :].strip()
        elif compact.startswith("private:"):
            public = False
            compact = compact[len("private:") :].strip()
        if not public:
            continue
        name = method_name(class_name, compact)
        if not name:
            continue
        methods.append(
            Method(
                name=name,
                static=bool(re.search(r"\bstatic\b", compact.split("(", 1)[0])),
                signature=compact[:240],
                line=class_line + rel_line,
            )
        )
    return tuple(methods)


def public_classes(repo: Path) -> list[PublicClass]:
    classes: list[PublicClass] = []
    seen: set[tuple[str, str, int]] = set()
    for path in public_header_paths(repo):
        for name, kind, rel, line, body in class_definitions(repo, path):
            key = (name, rel, line)
            if key in seen:
                continue
            seen.add(key)
            classes.append(
                PublicClass(
                    name=name,
                    kind=kind,
                    path=rel,
                    area=area_for(rel),
                    line=line,
                    methods=extract_methods(name, kind, body, line),
                )
            )
    return classes


def capi_function_names(repo: Path) -> set[str]:
    functions: set[str] = set()
    pattern = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")
    for path in sorted((repo / "skia/capi").glob("*.h")):
        text = strip_comments(path.read_text(errors="ignore"))
        for line in text.splitlines():
            if line.lstrip().startswith("#"):
                continue
            if ";" not in line and "{" not in line:
                continue
            match = pattern.search(line)
            if not match:
                continue
            name = match.group(1)
            if name in {"if", "for", "while", "switch", "return", "sizeof"}:
                continue
            functions.add(name)
    return functions


def class_prefix_candidates(class_name: str, path: str) -> set[str]:
    names = {class_name}
    if path.startswith("modules/skottie/") and class_name == "Animation":
        names.add("Skottie_Animation")
    if path.startswith("modules/sksg/"):
        names.add("SkSG_" + class_name)
    if path.startswith("modules/skparagraph/"):
        names.add("SkParagraph_" + class_name)
    if path.startswith("modules/svg/"):
        names.add(class_name)
    return names


def method_token(method: Method) -> str:
    name = method.name
    if name.startswith("~"):
        return "delete"
    if name == "operator==":
        return "equals"
    if name == "operator!=":
        return "notEquals"
    if name == "operator=":
        return "assign"
    if name == "operator()":
        return "call"
    if name == "operator+":
        return "add"
    if name == "operator-":
        if re.search(r"\(\s*\)", method.signature):
            return "negate"
        return "subtract"
    if name == "operator*":
        return "multiply"
    if name == "operator+=":
        return "addAssign"
    if name == "operator-=":
        return "subtractAssign"
    if name == "operator*=":
        if "SkScalar" in method.signature:
            return "multiplyScalarAssign"
        return "multiplyAssign"
    if name == "operator/=":
        return "divideScalarAssign"
    if name == "operator[]":
        return "at"
    if name.startswith("operator"):
        return name.replace("operator", "operator_").replace("=", "assign").replace("==", "eq")
    return name


def status_for_method(cls: PublicClass, method: Method, functions: set[str]) -> tuple[str, str]:
    prefixes = class_prefix_candidates(cls.name, cls.path)
    token = method_token(method)
    exact: list[str] = []
    loose: list[str] = []

    if method.name == cls.name:
        constructor_terms = ("new", "make", "Make", "Create", "New")
        for fn in functions:
            matching_prefixes = [prefix for prefix in prefixes if fn.startswith(prefix + "_")]
            for prefix in matching_prefixes:
                suffix = fn[len(prefix) + 1:]
                if suffix.startswith(constructor_terms) or suffix in constructor_terms:
                    exact.append(fn)
                    break
        return ("covered" if exact else "missing", "|".join(sorted(exact)[:8]))

    for prefix in prefixes:
        expected = prefix + "_" + token
        for fn in functions:
            if fn == expected:
                exact.append(fn)
            elif fn.startswith(expected):
                loose.append(fn)

    if exact:
        return "covered", "|".join(sorted(exact)[:8])
    if loose:
        return "partial", "|".join(sorted(loose)[:8])
    return "missing", ""


def status_for_class(cls: PublicClass, functions: set[str]) -> tuple[str, str]:
    prefixes = class_prefix_candidates(cls.name, cls.path)
    hits = sorted(fn for fn in functions if any(fn.startswith(prefix + "_") for prefix in prefixes))
    if hits:
        return "covered", "|".join(hits[:8])
    refs = sorted(fn for fn in functions if cls.name in fn)
    if refs:
        return "referenced", "|".join(refs[:8])
    return "missing", ""


def write_matrix(repo: Path, output: Path) -> None:
    classes = public_classes(repo)
    functions = capi_function_names(repo)
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(
            [
                "area",
                "header",
                "class",
                "class_kind",
                "class_line",
                "class_status",
                "method",
                "method_line",
                "method_static",
                "method_status",
                "matched_capi",
                "signature",
                "note",
            ]
        )
        for cls in classes:
            class_status, class_match = status_for_class(cls, functions)
            if not cls.methods:
                writer.writerow(
                    [
                        cls.area,
                        cls.path,
                        cls.name,
                        cls.kind,
                        cls.line,
                        class_status,
                        "",
                        "",
                        "",
                        "no_public_methods_found",
                        class_match,
                        "",
                        "public method extraction found no methods",
                    ]
                )
                continue
            for method in cls.methods:
                method_status, method_match = status_for_method(cls, method, functions)
                writer.writerow(
                    [
                        cls.area,
                        cls.path,
                        cls.name,
                        cls.kind,
                        cls.line,
                        class_status,
                        method.name,
                        method.line,
                        "yes" if method.static else "no",
                        method_status,
                        method_match or class_match,
                        method.signature,
                        "",
                    ]
                )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo", type=Path, default=Path.cwd())
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv"),
    )
    args = parser.parse_args()
    write_matrix(args.repo.resolve(), (args.repo / args.output).resolve() if not args.output.is_absolute() else args.output)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
