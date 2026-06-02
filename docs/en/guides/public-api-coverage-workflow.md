# Public API Coverage Workflow

This document describes how Reskia checks coverage between Skia public APIs and Reskia C APIs.

## Purpose

Reskia exposes Skia public APIs through a C ABI where practical. Progress is tracked with a coverage matrix.

The coverage workflow checks:

- Skia public classes and methods in upstream headers.
- Whether Reskia has corresponding C APIs.
- Why an API is not exposed.
- Whether Skia upgrades leave stale C APIs behind.

## Main Files

| Path | Role |
| --- | --- |
| `scripts/generate_public_api_coverage.py` | Coverage matrix generator. |
| `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` | Current coverage matrix. |
| `docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv` | Stale C API report for upstream-removed APIs. |
| `vendor/skia-upstream` | Reference Skia public headers for the accepted baseline. |
| `vendor/skia-upstream-candidate` | Reference headers for upgrade candidates. |

## Reading the Matrix

The matrix records Reskia status for each Skia public API row.

Important statuses:

| status | Meaning |
| --- | --- |
| `covered` | A corresponding C API exists. |
| `split_covered` | One Skia API is represented by multiple C APIs. |
| `false_positive` | The generator detected a row that is not a real target. |
| `na` | There is a reason not to expose it through C ABI. |
| `missing` | Work is needed. |
| `deferred` | Follow-up work. This should normally remain zero. |
| `partial` | Partially covered. This should normally remain zero. |
| `overcovered` | Reskia may expose more than the upstream public API. This should normally remain zero. |

The normal goal is to keep `missing` / `deferred` / `partial` / `overcovered` at zero.

## Baseline Regeneration

Regenerate the matrix against the accepted baseline:

```bash
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream \
  --output docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv
```

If the stale report contains only the header row, no C API for a removed upstream public API was detected.

## Candidate Probe

During a Skia upgrade, run the generator against the candidate checkout before updating the lock.

```bash
mkdir -p .tmp/skia-upgrade-cycle-XXX
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream-candidate \
  --output .tmp/skia-upgrade-cycle-XXX/candidate-public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output .tmp/skia-upgrade-cycle-XXX/candidate-stale-capi.csv
```

Review:

- Whether `missing` increased.
- Whether `deferred`, `partial`, or `overcovered` appeared.
- Whether stale C APIs were detected.
- Whether optional-module or platform-dependency reasons are still valid.

## Overrides

Use override CSV files for cases the generator cannot classify automatically.

Overrides are not for hiding debt. Use them for cases such as:

- Unsafe or unsuitable C ABI shape.
- Optional module or platform dependency.
- Templates, private helpers, callback-heavy APIs, or similar cases that should not be exposed directly.
- APIs covered by another name or split APIs.
- Generator false positives.

When adding an override, write a short, concrete reason.

## Stale C API Report

When Skia removes or changes a public API, Reskia may still contain old C APIs. `--stale-output` reports those candidates.

When a stale row appears:

1. Confirm that upstream really removed or changed the API.
2. Decide whether Reskia should keep the C API for compatibility.
3. Record the reason if keeping it.
4. If removing it, update C API headers, implementations, source lists, tests, and docs.

## Change Checklist

After adding, removing, or renaming C APIs:

1. Public headers and implementations match.
2. Source lists are updated.
3. Ownership and lifetime comments exist.
4. Smoke tests are added where needed.
5. The coverage matrix regenerates.
6. The stale report matches expectations.
7. The build passes.

## Related Documents

- `docs/en/guides/c-api-bindings-overview.md`
- `docs/en/guides/c-api-safety-guidelines.md`
- `docs/en/guides/skia-upgrade-workflow.md`
