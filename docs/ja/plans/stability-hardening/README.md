# Reskia Stability Hardening Plan

作成日時: 2026-05-08 12:13:52 JST

Reskia の安全性と安定性を高めるための横断計画です。

## 目的

- `skia/capi` / `skia/handles` の所有権、寿命、無効入力処理を安定させる。
- `RESKIA_BUILD_TESTS=ON` と `ctest` を信頼できる標準検証経路にする。
- sanitizer と smoke test により、C ABI 境界のメモリ破壊・未定義動作・stale handle 誤用を早期検出する。
- platform / dependency / feature flag の制約を、失敗しやすい暗黙条件から明示条件へ寄せる。
- 機能追加より先に、既存 API の運用リスクを下げる。

## 進捗記録

Phase 2 の C API safety batch では、従来の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` に加えて、`docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv` を更新する。`capi-status.csv` はファイル単位の集約、`capi-safety-detail-status.csv` は API 群 + 安全性規約単位の詳細台帳である。

バッチ開始前には詳細台帳を検索し、同じ `area` / `api_pattern` / `rule_category` が確認済みでないかを見る。バッチ完了時には、確認した API 群ごとに implementation / header / smoke / valid path の状態を残し、バッチ記録の「変更内容」に更新した detail row の `id` を書く。

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
- `62-phase-2-batch-bi-canvas-recheck.md`
- `63-phase-2-batch-bj-font-callback-recheck.md`
- `64-phase-2-batch-bk-mesh-specification.md`
- `65-phase-2-batch-bl-mesh.md`
- `66-phase-2-batch-bm-file-streams.md`
- `67-phase-2-batch-bn-op-builder.md`
- `68-phase-2-batch-bo-pathops.md`
- `69-phase-2-batch-bp-document-dynamic-stream.md`
- `70-phase-2-batch-bq-encoded-cubic.md`
- `71-phase-2-batch-br-annotation-android-codec.md`
- `72-phase-2-batch-bs-canvas-text-glyphs.md`
- `73-phase-2-batch-bt-font-widths-bounds.md`
- `74-phase-2-batch-bu-auto-canvas-restore-bbox.md`
- `75-phase-2-batch-bv-canvas-atlas-image-set.md`
- `76-phase-2-batch-bw-font-positions-intercepts.md`
- `77-phase-2-batch-bx-canvas-layer-raster-direct.md`
- `78-phase-2-batch-by-canvas-image-handles.md`
- `79-phase-2-batch-bz-font-text-encoding.md`
- `80-phase-2-batch-ca-canvas-pixels-rowbytes.md`
- `81-phase-2-batch-cb-canvas-image-lattice-nine.md`
- `82-phase-2-batch-cc-text-blob-text-buffers.md`
- `83-phase-2-batch-cd-canvas-top-layer-pixels.md`
- `84-phase-2-batch-ce-surface-pixels-rowbytes.md`
- `85-phase-2-batch-cf-canvas-text-blob-draw.md`
- `86-phase-2-batch-cg-canvas-drawable-picture.md`
- `87-phase-2-batch-ch-surface-async-read.md`
- `88-phase-2-batch-ci-canvas-vertices-draw.md`
- `89-phase-2-batch-cj-canvas-string-draw.md`
- `90-phase-2-batch-ck-image-async-read.md`
- `91-phase-2-batch-cl-runtime-effect-source-handle.md`
- `92-phase-2-batch-cm-canvas-paint-path-region.md`
- `93-phase-2-batch-cn-image-shader-guards.md`
- `94-phase-2-batch-co-runtime-effect-make-traced.md`
- `95-phase-2-batch-cp-canvas-patch.md`
- `96-phase-2-batch-cq-image-read-pixels.md`
- `97-phase-2-batch-cr-runtime-effect-data-child.md`
- `98-phase-2-batch-cs-canvas-rrect-draw.md`
- `99-phase-2-batch-ct-image-factory-handles.md`
- `100-phase-2-batch-cu-runtime-effect-result-ownership.md`
- `101-phase-2-batch-cv-canvas-rect-draw.md`
- `102-phase-2-batch-cw-image-color-space-handles.md`
- `103-phase-2-batch-cx-runtime-effect-generated-handles.md`
- `104-phase-2-batch-cy-canvas-point-line.md`
- `105-phase-2-batch-cz-canvas-circle-arc.md`
- `106-phase-2-batch-da-image-color-space-accessors.md`
- `107-phase-2-batch-db-runtime-effect-blender-ownership.md`
- `108-phase-2-batch-dc-canvas-color-draw.md`
- `109-phase-2-batch-dd-image-encoded-data.md`
- `110-phase-2-batch-de-runtime-effect-builder-generated-handles.md`
- `111-phase-2-batch-df-canvas-annotation.md`
- `112-phase-2-batch-dg-image-scale-pixels.md`
- `113-phase-2-batch-dh-runtime-effect-uniform-child-spans.md`

## 関連計画

- `docs/ja/plans/c-binding-remediation/`
- `docs/ja/plans/cmake-remediation/`
- `docs/ja/plans/gpu-enablement/`
- `docs/ja/plans/skparagraph-enablement/`

## 関連ガイド

- `docs/ja/guides/c-api-safety-guidelines.md`

## 引き継ぎ

- `handoff-2026-05-10-0805.md`

## 参照メモ

- `docs/ja/notes/project-overview-and-next-tasks-2026-05-06.md`
- `docs/ja/notes/bindings/capi-and-handle-binding-coverage-survey-2026-05-06.md`
- `docs/ja/notes/bindings/core-effects-missing-triage-2026-05-06.md`
- `docs/ja/notes/bindings/phase-a-api-coverage-progress-2026-05-06.md`
- `docs/ja/notes/bindings/phase-c-callback-registration-progress-2026-05-06.md`
- `docs/ja/notes/bindings/phase-d-async-read-progress-2026-05-06.md`
