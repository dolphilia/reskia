# Skia Incremental Upgrade Readiness

作成時刻: 2026-05-22 07:29:54 JST

## Summary

`vendor/skia-upstream` を徐々に新しい Skia commit へ進め、Reskia の C API binding と CMake source sync を段階的に追従する作業に入れるかを調査した。

結論:

- 段階的アップグレードの探索を始める土台は整っている。
- ただし、`vendor/skia-source.lock` を即座に最新 main へ更新する段階ではない。
- まずは候補 commit を一時 checkout し、public API diff、source/header sync diff、coverage regression、build smoke を記録する "upgrade probe" phase を挟むべき。
- 現在の coverage freeze (`missing 0` / `deferred 0`) と Phase 30-33 の verification matrix は、upgrade probe の合否判定として使える。

## Current Baseline

Skia baseline:

- `vendor/skia-source.lock`
- `SKIA_REF=0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- `SKIA_BASELINE_DATE=2026-02-14`

Local `vendor/skia-upstream`:

- HEAD: `0d49b661d7`
- status: clean
- current remote observed during this investigation: `https://github.com/dolphilia/skia.git`
- lock file upstream URL: `https://github.com/google/skia.git`

This remote mismatch is not fatal because `scripts/fetch_skia_upstream.sh` resets remotes from the lock file, but it is a reminder that upgrade work should always start by running the fetch script rather than relying on the current clone configuration.

Coverage freeze:

| status | count |
| --- | ---: |
| `covered` | 2811 |
| `split_covered` | 33 |
| `false_positive` | 275 |
| `na` | 198 |
| `no_public_methods_found` | 104 |
| `missing` | 0 |
| `deferred` | 0 |
| `partial` | 0 |
| `overcovered` | 0 |
| total | 3421 |

Recent verification baseline:

- prebuilt `reskia` build: pass
- source `reskia` build: pass
- GPU prebuilt smoke: pass, with Metal device unavailable reported as `SKIP` then `PASS`
- source SVG/provider smoke: pass
- coverage generator: pass

## Upstream Reality

Skia's official documentation identifies `skia.googlesource.com/skia` as the canonical source tree. The official download documentation describes cloning from `https://skia.googlesource.com/skia.git` and running Skia's dependency sync tools. The Gitiles main branch is actively moving; during this investigation, the public main page showed commits from the previous few hours.

Implication for Reskia:

- "latest" should mean a pinned commit, not a floating branch.
- Every upgrade step should record a candidate Skia commit hash.
- The lock file should be updated only after the candidate passes coverage and build gates.

References:

- https://skia.org/docs/
- https://docs.skia.org/docs/user/download/
- https://skia.googlesource.com/skia.git/

## Existing Upgrade Assets

### Lock + fetch workflow

`docs/notes/vendor-skia-management-2026-02-14.md` already chose a lock + untracked clone model:

- `vendor/skia-source.lock` tracks the source URLs and fixed ref.
- `scripts/fetch_skia_upstream.sh` can clone/fetch `vendor/skia-upstream`.
- `--ref` supports temporary candidate checkout.
- `--dest` supports checking out a candidate into another directory.

This is a good fit for incremental upgrades because each candidate can be tested without making `vendor/skia-upstream` a tracked submodule.

### Public API coverage generator

`scripts/generate_public_api_coverage.py` extracts public headers from `vendor/skia-upstream` and compares method-level public API coverage against `skia/capi`.

This is now strong enough to be an upgrade gate because Phase 29-33 closed the steady-state matrix:

- `missing` must remain 0 after an accepted upgrade.
- New public APIs from upstream should become `missing` during probe, then be implemented or classified.
- `false_positive` / `na` / `split_covered` can absorb generator or platform noise when justified.

### Verification matrix

Phase 30 and Phase 33 established a practical build gate:

- coverage generator
- prebuilt `reskia`
- source `reskia`
- GPU prebuilt smoke
- source SVG/provider smoke

This is enough to judge small candidate bumps.

## Readiness Assessment

Ready:

- Baseline Skia ref is pinned.
- Local comparison tree exists and is clean.
- C API coverage is frozen at `missing 0` / `deferred 0`.
- Callback/provider ownership policies are documented.
- Optional backend `na` policy is documented.
- Representative build/smoke matrix exists and passes.
- Fetch script supports temporary refs.

Not fully ready:

- There is no first-class "compare two Skia refs and emit public API delta" script.
- `generate_public_api_coverage.py` assumes `vendor/skia-upstream` as the source tree; it does not directly accept a separate candidate Skia checkout path.
- Source/header sync from upstream into `skia/` is still area-specific and manual.
- Skia dependency changes from `DEPS`, `gn/*.gni`, generated files, and optional third_party rolls are not automatically classified.
- The current local `vendor/skia-upstream` remote points at the fork until the fetch script resets it.
- The local clone appears grafted/shallow from the checked-out baseline, so local history alone is not sufficient for commit-range planning.

Overall:

- Proceed with a bounded upgrade probe.
- Do not update `vendor/skia-source.lock` to a new baseline until the first probe has a repeatable diff/build report.

## Recommended Upgrade Strategy

Use three nested levels:

1. Probe commit
2. Accepted bump
3. Baseline lock update

### Level 1: Probe commit

Goal: measure drift without committing to it.

Recommended steps:

1. Select a candidate commit.
   - Prefer small, dated checkpoints over `main`.
   - Avoid jumping directly from 2026-02-14 baseline to current main.
2. Fetch candidate.
   - Use `scripts/fetch_skia_upstream.sh --ref <candidate>`.
   - Or use `--dest vendor/skia-upstream-candidate` if keeping the baseline checkout untouched is preferred.
3. Run public API coverage.
   - `python3 scripts/generate_public_api_coverage.py`
   - Record new `missing` / `partial` / `overcovered` / `deferred`.
4. Diff public headers by area.
   - `include/core`
   - `include/effects`
   - `include/utils`
   - `modules/*/include`
   - `include/gpu`
5. Diff source list dependencies.
   - `gn/*.gni`
   - `DEPS`
   - module source directories already mirrored into `skia/`
6. Run representative build/smoke matrix only after source/header sync is attempted.

Probe output should be a note under `docs/notes/` with:

- candidate commit
- public API delta summary
- expected coverage debt
- source sync risk
- dependency risk
- build result
- accept/reject recommendation

### Level 2: Accepted bump

Goal: make Reskia compile against the candidate Skia snapshot.

Recommended order:

1. Start with public headers and low-risk source sync.
2. Regenerate coverage and classify new rows.
3. Implement C ABI wrappers for low-risk new public methods.
4. Add `na` / `false_positive` overrides only with explicit reasons.
5. Run Phase 30/33 verification matrix.
6. Record all CMake/source-list changes.

Accepted bump should still be one small Skia candidate, not a broad latest jump.

### Level 3: Baseline lock update

Goal: make the candidate the new official Reskia baseline.

Only do this after:

- coverage returns to `missing 0` / `deferred 0`
- representative builds pass
- source sync notes are written
- optional backend changes are classified
- `vendor/skia-source.lock` is updated with the accepted commit and date

## Candidate Selection

Do not use floating `main` directly.

Recommended candidate types:

1. A specific commit from official `main`.
2. A dated checkpoint commit selected from Skia Gitiles.
3. A commit known to match a dependency roll boundary if dependency changes are the focus.

Initial bump size:

- Start with 1-2 weeks after `0d49b661...`.
- If the diff is small and builds are clean, increase to monthly checkpoints.
- If the diff is large, split by feature area instead of time.

Why:

- The current baseline is from 2026-02-14.
- Current upstream main is months ahead and actively rolling dependency repositories.
- A direct jump would mix public API drift, source-list drift, dependency drift, and optional backend drift in one review.

## Proposed Phases

### Phase U0: Upgrade Probe Tooling

Scope:

- Add or document a repeatable probe checklist.
- Prefer adding a script that can compare current baseline vs candidate public header extraction.
- Consider adding `--skia-root` to `scripts/generate_public_api_coverage.py` so candidate checkouts do not have to replace `vendor/skia-upstream`.

Exit criteria:

- Can produce a public API delta report without changing `vendor/skia-source.lock`.

### Phase U1: First Small Skia Bump Probe

Scope:

- Choose a small candidate after `0d49b661...`.
- Fetch candidate into `vendor/skia-upstream` or a temporary candidate checkout.
- Run coverage generator.
- Record public API delta and build risk.

Exit criteria:

- A probe note says whether the candidate is safe to accept.

### Phase U2: Low-Risk Core/Effects/Utils Sync

Scope:

- Only sync public headers and source files for low-risk areas.
- Avoid GPU, text shaping, Skottie, Graphite, Dawn/Vulkan/D3D changes.
- Bring coverage back to freeze.

Exit criteria:

- prebuilt/source `reskia` builds pass.
- coverage returns to `missing 0`.

### Phase U3: Module Sync

Scope:

- SVG / skresources / skunicode / skshaper / skparagraph changes.
- Respect optional dependency gates.

Exit criteria:

- source SVG/provider smoke passes.
- text stack smoke passes where enabled.

### Phase U4: GPU/Graphite Sync

Scope:

- Ganesh/Graphite public header and source drift.
- Optional backend rows stay behind Phase 32 roadmap unless a backend-specific bridge is planned.

Exit criteria:

- GPU prebuilt smoke builds and exits `PASS` or expected `SKIP`/`PASS`.
- New GPU public APIs are implemented or classified.

### Phase U5: Lock Update

Scope:

- Update `vendor/skia-source.lock`.
- Record accepted commit and date.
- Regenerate final coverage matrix.
- Run Phase 33 build sweep.

Exit criteria:

- The candidate becomes the new baseline.

## Immediate Recommendation

Proceed, but start with Phase U0 rather than changing the lock.

The next concrete task should be:

1. Add candidate-comparison tooling or a documented manual checklist.
2. Select a first small candidate commit.
3. Run a probe that intentionally does not update `vendor/skia-source.lock`.

This keeps the current stable freeze intact while making upgrade risk visible.
