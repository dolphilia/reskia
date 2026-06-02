# Phase 29 Final Coverage Freeze / Documentation Closeout

作成時刻: 2026-05-21 20:03:32 JST

## Summary

Phase 28 で Ganesh external texture dedicated bridge を実装し、Phase 26 で意図的に残していた `deferred 5` は 0 になった。

この note は、Skia public class C API coverage の method-level matrix について、Phase 29 時点の最終 coverage freeze として扱う基準を固定する。

## Coverage Snapshot

対象ファイル:

- `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`

生成コマンド:

```sh
python3 scripts/generate_public_api_coverage.py
```

Phase 29 snapshot:

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

## Freeze Invariants

- `missing` / `deferred` / `partial` / `overcovered` は通常状態で 0 を維持する。
- 新しい Skia header 追従、generator 改修、または override 追加で 0 以外に戻った場合は、同じ変更内で実装・分類・設計メモのいずれかに routing する。
- `false_positive` は extractor/generator の既知限界による行であり、実装 backlog として扱わない。
- `na` は platform-only、private/internal、unsupported optional backend、または C ABI に安全に出すべきでない API として明示分類済みの行であり、実装 backlog として扱わない。
- `no_public_methods_found` は public class discovery の結果であり、method binding debt として扱わない。
- `split_covered` は C ABI 上で複数の safer helper に分割して公開した API として扱う。

## Verification Baseline

Phase 29 freeze に直接使った検証:

- `python3 scripts/generate_public_api_coverage.py`
- status count audit: `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`

Phase 27-28 で直近確認済みの build/runtime baseline:

- `cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke -j 8`
- `skia/cmake-build-codex-phase9-gpu/test_gpu_context_capi_smoke`
  - 現在環境では Metal device unavailable により Graphite/Metal path は skip
  - Ganesh external texture bridge smoke は `PASS`
- `cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_image_capi_smoke -j 8`
- `skia/cmake-build-codex-phase3-svg-source/test_svg_image_capi_smoke`

## Documentation Closeout

Phase 29 以降は、coverage の数字を増やす段階から、coverage 状態を壊さないための freeze maintenance に移る。

次に着手する価値がある作業は、実装追加ではなく次の順になる。

1. Phase 30: Verification Matrix Hardening
2. Phase 31: Header / Naming / Ownership Audit
3. Phase 32: Optional Backend Roadmap
4. Phase 33: Full Build Sweep

これらは `missing 0` / `deferred 0` を前提に、ビルド構成・命名・所有権・optional backend の長期保守性を固めるための follow-up として扱う。
