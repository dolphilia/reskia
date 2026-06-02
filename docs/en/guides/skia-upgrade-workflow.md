# Skia Upgrade Workflow

This document describes the standard workflow for tracking upstream Skia in Reskia.

Detailed cycle plans and history live under `docs/ja/plans/skia-incremental-upgrade/`. This guide keeps only the recurring rules and decisions.

## Basic Policy

Skia tracking uses the fixed commit in `vendor/skia-source.lock` as the current baseline.

Rules:

1. Do not use a floating `main` branch as the baseline.
2. Pin each candidate by commit hash.
3. Do not update `vendor/skia-source.lock` until the probe passes.
4. Check public API coverage, stale C APIs, source drift, and build / smoke results.
5. Record the cycle result in the cycle record and HANDOFF.

## Main Files

| Path | Role |
| --- | --- |
| `vendor/skia-source.lock` | Accepted Skia commit. |
| `vendor/skia-upstream` | Reference checkout for the accepted baseline. |
| `vendor/skia-upstream-candidate` | Candidate checkout for upgrade probes. |
| `docs/ja/plans/skia-incremental-upgrade/HANDOFF.md` | Handoff for the next cycle. |
| `docs/ja/plans/skia-incremental-upgrade/records/` | Cycle records. |
| `scripts/generate_public_api_coverage.py` | Candidate coverage and stale C API checks. |

## One Cycle

### 1. Baseline Check

Check the current state.

```bash
git branch --show-current
git status --short --branch
cat vendor/skia-source.lock
git -C vendor/skia-upstream rev-parse HEAD
git -C vendor/skia-upstream status --short --branch
```

Do not change the lock in this step.

### 2. Candidate Selection

Choose exactly one Skia commit to probe.

Selection criteria:

- It can be pinned by commit hash.
- It exists in local refs.
- The diff from baseline is not too large.
- Public header diff, source drift, and dependency drift can be explained.
- If a large dependency roll or backend migration appears, shrink the candidate range.

Example checks:

```bash
baseline=$(sed -n 's/^SKIA_REF="//p' vendor/skia-source.lock | sed 's/"$//')
git -C vendor/skia-upstream show -s --format='%H%n%cI%n%s' <candidate>
git -C vendor/skia-upstream rev-list --count "$baseline"..<candidate>
git -C vendor/skia-upstream diff --shortstat "$baseline"..<candidate> -- include modules
git -C vendor/skia-upstream diff --name-status "$baseline"..<candidate> -- include modules
```

### 3. Probe Without Lock Update

Prepare the candidate checkout and measure the diff without changing the lock.

```bash
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream-candidate \
  --output .tmp/skia-upgrade-cycle-XXX/candidate-public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output .tmp/skia-upgrade-cycle-XXX/candidate-stale-capi.csv
```

Check:

- Public API coverage regression.
- Stale C APIs.
- Drift in `DEPS`, `gn`, and Bazel metadata.
- Added or removed mirrored source directories.
- Optional backend or platform dependency impact.

### 4. Routing

Classify the probe result.

| Category | Response |
| --- | --- |
| Source sync only | Sync source lists or missing files. |
| C API catch-up | Update headers, implementations, tests, and matrix rows. |
| Optional backend drift | Review feature flags, guards, and unsupported reasons. |
| Tooling gap | Fix coverage generator or stale reporting first. |
| Candidate too large | Record it as deferred and choose a smaller range. |

### 5. Verification Gate

At minimum, run:

```bash
git diff --check
cmake -S skia -B skia/cmake-build-upgrade-prebuilt -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-upgrade-prebuilt -j 8
```

Depending on the change, also run source mode, feature smoke tests, coverage regeneration, and stale C API checks.

### 6. Lock Update

Only after probe, routing, and verification pass, update `vendor/skia-source.lock` to the candidate commit.

After updating the lock:

- Align `vendor/skia-upstream` with the accepted commit.
- Regenerate the coverage matrix against the accepted baseline.
- Check the stale C API report.
- Update the cycle record and HANDOFF.

## Stop Conditions

Do not update the lock when:

- The candidate does not exist in local refs.
- The coverage generator cannot process the candidate.
- Stale C API decisions are unfinished.
- Build or smoke tests fail without a clear explanation.
- A dependency roll or backend migration is too large for the current cycle.

When stopping, record the candidate, the reason, and the next check in HANDOFF.

## Related Documents

- `docs/en/guides/public-api-coverage-workflow.md`
- `docs/en/guides/repository-structure.md`
- `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md`
- `docs/ja/plans/skia-incremental-upgrade/HANDOFF.md`
