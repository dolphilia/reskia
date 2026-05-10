# Reskia Stability Hardening Plan

作成日時: 2026-05-08 12:13:52 JST

Reskia の安全性と安定性を高めるための横断計画です。

## 目的

- `skia/capi` / `skia/handles` の所有権、寿命、無効入力処理を安定させる。
- `RESKIA_BUILD_TESTS=ON` と `ctest` を信頼できる標準検証経路にする。
- sanitizer と smoke test により、C ABI 境界のメモリ破壊・未定義動作・stale handle 誤用を早期検出する。
- platform / dependency / feature flag の制約を、失敗しやすい暗黙条件から明示条件へ寄せる。
- 機能追加より先に、既存 API の運用リスクを下げる。

## 計画書一覧

- `00-plan.md`
- `01-phase-1-checklist-alignment.md`
- `02-phase-2-batch-a-capi-safety.md`
- `03-phase-2-batch-b-bitmap.md`
- `04-phase-2-batch-c-path.md`
- `05-phase-2-batch-d-paint.md`
- `06-phase-2-batch-e-rect-rrect.md`
- `07-phase-2-batch-f-image-info.md`
- `08-phase-2-batch-g-data.md`
- `09-phase-2-batch-h-stream-memory-stream.md`
- `10-phase-2-batch-i-wstream.md`
- `11-phase-2-batch-j-stream-derived.md`
- `12-phase-2-batch-k-color-info-space.md`
- `13-phase-2-batch-l-path-effect.md`
- `14-phase-2-batch-m-color-filter.md`
- `15-phase-2-batch-n-color-values.md`
- `16-phase-2-batch-o-color-matrix-filter.md`
- `17-phase-2-batch-p-color-core.md`
- `18-phase-2-batch-q-contour-path-measure.md`
- `19-phase-2-batch-r-data-table.md`
- `20-phase-2-batch-s-color-table.md`
- `21-phase-2-batch-t-mask-filter.md`
- `22-phase-2-batch-u-mask.md`
- `23-phase-2-batch-v-matrix.md`
- `24-phase-2-batch-w-m44.md`
- `25-phase-2-batch-x-vector.md`
- `26-phase-2-batch-y-vertices.md`
- `27-phase-2-batch-z-font-style.md`
- `28-phase-2-batch-aa-font.md`
- `29-phase-2-batch-ab-typeface.md`
- `30-phase-2-batch-ac-font-arguments-metrics.md`
- `31-phase-2-batch-ad-drawable-flattenable.md`
- `32-phase-2-batch-ae-picture-recorder.md`
- `33-phase-2-batch-af-font-mgr.md`
- `34-phase-2-batch-ag-typeface-mac.md`
- `35-phase-2-batch-ah-overdraw-canvas.md`
- `36-phase-2-batch-ai-read-write-buffer.md`
- `37-phase-2-batch-aj-region.md`
- `38-phase-2-batch-ak-text-blob.md`
- `39-phase-2-batch-al-raster-handle-allocator.md`
- `40-phase-2-batch-am-ref-cnt.md`
- `41-phase-2-batch-an-pixel-ref.md`
- `42-phase-2-batch-ao-pixmap.md`
- `43-phase-2-batch-ap-yuva-pixmaps.md`
- `44-phase-2-batch-aq-yuva-info.md`
- `45-phase-2-batch-ar-read-write-buffer-completion.md`
- `46-phase-2-batch-as-codec.md`
- `47-phase-2-batch-at-decoders.md`
- `48-phase-2-batch-au-encoders.md`
- `49-phase-2-batch-av-image-generator.md`
- `50-phase-2-batch-aw-open-type-svg-decoder.md`
- `51-phase-2-batch-ax-image-filters.md`
- `52-phase-2-batch-ay-shaders.md`
- `53-phase-2-batch-az-blenders.md`
- `54-phase-2-batch-ba-path-effect-recheck.md`
- `55-phase-2-batch-bb-text-blob-run-handler.md`
- `56-phase-2-batch-bc-blender.md`
- `57-phase-2-batch-bd-path-builder.md`
- `58-phase-2-batch-be-tiled-image-utils.md`
- `59-phase-2-batch-bf-runtime-effect.md`
- `60-phase-2-batch-bg-surface-props-surfaces.md`
- `61-phase-2-batch-bh-images-recheck.md`

## 関連計画

- `docs/plans/c-binding-remediation/`
- `docs/plans/cmake-remediation/`
- `docs/plans/gpu-enablement/`
- `docs/plans/skparagraph-enablement/`

## 引き継ぎ

- `handoff-2026-05-10-0805.md`

## 参照メモ

- `docs/notes/project-overview-and-next-tasks-2026-05-06.md`
- `docs/notes/bindings/capi-and-handle-binding-coverage-survey-2026-05-06.md`
- `docs/notes/bindings/core-effects-missing-triage-2026-05-06.md`
- `docs/notes/bindings/phase-a-api-coverage-progress-2026-05-06.md`
- `docs/notes/bindings/phase-c-callback-registration-progress-2026-05-06.md`
- `docs/notes/bindings/phase-d-async-read-progress-2026-05-06.md`
