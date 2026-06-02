# vendor

This directory stores the Skia source lock and local reference checkouts used
when Reskia tracks upstream Skia.

## Files

- `skia-source.lock`: tracked lock file containing the accepted Skia source URL
  and commit.
- `skia-upstream/`: local checkout of the accepted baseline, ignored by git.
- `skia-upstream-candidate/`: optional local checkout for upgrade probes,
  ignored by git.

## Current Baseline

- `SKIA_REF=70f9d90bc8e6a56101d036153cfef28088e57f5b`
- `SKIA_BASELINE_DATE=2026-06-01`

Fetch or refresh the local reference checkout with:

```bash
scripts/fetch_skia_upstream.sh
```

## Upgrade Rule

During an incremental Skia upgrade, do not update `skia-source.lock` until the
candidate commit has passed probe and verification.

Always treat upgrade candidates as fixed commit hashes. Do not use a floating
`main` branch as the baseline or as an accepted candidate.

## Related Documents

- `docs/en/guides/skia-upgrade-workflow.md`
- `docs/ja/plans/skia-incremental-upgrade/`
