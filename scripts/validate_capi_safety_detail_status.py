#!/usr/bin/env python3
"""Validate the C API safety detail status checklist."""

from __future__ import annotations

import argparse
import csv
import sys
from pathlib import Path


DEFAULT_CHECKLIST = Path(
    "docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv"
)
STABILITY_DIR = Path("docs/plans/stability-hardening")

EXPECTED_FIELDS = [
    "id",
    "area",
    "api_pattern",
    "files",
    "rule_category",
    "receiver_rule",
    "input_rules",
    "output_or_lifetime_rule",
    "invalid_behavior",
    "implementation_status",
    "header_status",
    "smoke_status",
    "valid_path_status",
    "last_batch",
    "last_checked_at",
    "evidence",
    "notes",
]

REQUIRED_FIELDS = [
    "id",
    "area",
    "api_pattern",
    "files",
    "rule_category",
    "receiver_rule",
    "input_rules",
    "output_or_lifetime_rule",
    "invalid_behavior",
    "implementation_status",
    "header_status",
    "smoke_status",
    "valid_path_status",
    "last_batch",
    "last_checked_at",
    "evidence",
]

ALLOWED_VALUES = {
    "implementation_status": {"not-started", "verified", "changed"},
    "header_status": {"missing", "documented", "updated"},
    "smoke_status": {"missing", "covered", "partial", "not-needed"},
    "valid_path_status": {
        "covered",
        "representative-valid-path",
        "omitted-with-reason",
    },
}


def repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def evidence_path(root: Path, value: str) -> Path:
    path = Path(value)
    if path.is_absolute():
        return path
    if len(path.parts) == 1:
        return root / STABILITY_DIR / path
    return root / path


def validate(path: Path) -> list[str]:
    root = repo_root()
    errors: list[str] = []
    seen_ids: dict[str, int] = {}

    try:
        with path.open(newline="") as handle:
            reader = csv.DictReader(handle)
            if reader.fieldnames != EXPECTED_FIELDS:
                errors.append(
                    "header mismatch: expected "
                    + ",".join(EXPECTED_FIELDS)
                    + " but got "
                    + ",".join(reader.fieldnames or [])
                )
                return errors

            for line_number, row in enumerate(reader, start=2):
                if None in row:
                    errors.append(f"line {line_number}: too many columns")
                missing_columns = [name for name, value in row.items() if value is None]
                if missing_columns:
                    errors.append(
                        f"line {line_number}: missing columns: {', '.join(missing_columns)}"
                    )

                row_id = (row.get("id") or "").strip()
                if row_id in seen_ids:
                    errors.append(
                        f"line {line_number}: duplicate id '{row_id}' "
                        f"(first seen on line {seen_ids[row_id]})"
                    )
                elif row_id:
                    seen_ids[row_id] = line_number

                for field in REQUIRED_FIELDS:
                    if not (row.get(field) or "").strip():
                        errors.append(f"line {line_number}: required field '{field}' is empty")

                for field, allowed in ALLOWED_VALUES.items():
                    value = (row.get(field) or "").strip()
                    if value and value not in allowed:
                        errors.append(
                            f"line {line_number}: invalid {field} '{value}', "
                            f"expected one of {', '.join(sorted(allowed))}"
                        )

                evidence = (row.get("evidence") or "").strip()
                if evidence and not evidence_path(root, evidence).exists():
                    errors.append(
                        f"line {line_number}: evidence '{evidence}' does not exist"
                    )
    except FileNotFoundError:
        errors.append(f"checklist not found: {path}")

    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "checklist",
        nargs="?",
        default=DEFAULT_CHECKLIST,
        type=Path,
        help="CSV checklist to validate",
    )
    args = parser.parse_args()

    path = args.checklist
    if not path.is_absolute():
        path = repo_root() / path

    errors = validate(path)
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1

    print(f"validated {path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
