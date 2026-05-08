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

## 関連計画

- `docs/plans/c-binding-remediation/`
- `docs/plans/cmake-remediation/`
- `docs/plans/gpu-enablement/`
- `docs/plans/skparagraph-enablement/`

## 参照メモ

- `docs/notes/project-overview-and-next-tasks-2026-05-06.md`
- `docs/notes/bindings/capi-and-handle-binding-coverage-survey-2026-05-06.md`
- `docs/notes/bindings/core-effects-missing-triage-2026-05-06.md`
- `docs/notes/bindings/phase-a-api-coverage-progress-2026-05-06.md`
- `docs/notes/bindings/phase-c-callback-registration-progress-2026-05-06.md`
- `docs/notes/bindings/phase-d-async-read-progress-2026-05-06.md`
