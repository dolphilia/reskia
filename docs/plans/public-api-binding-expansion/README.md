# Public API Binding Expansion Plan

- 作成日: 2026-05-14
- 作業開始時刻: 2026-05-14 13:33:02 JST
- 対象: Skia 公開クラスの public method / static factory / helper の C API バインディング拡充

## 目的

Reskia の C API バインディング方針である「Skia の公開クラスについて、公開メソッドと static factory/helper を可能な限り C ABI に露出する」を、今後の実装順序と検証単位に落とし込む。

この計画は、既存の安全性改善が一段落した後の coverage 拡大を対象にする。`skia/capi` のポインタ境界 API と `skia/handles` の整数ハンドル API の既存規約を前提に、optional module、platform dependency、所有権、callback、ABI 安全性を同時に管理する。

## 計画書一覧

- `00-current-state-and-roadmap.md`
- `01-callback-global-registration-design.md`
- `02-phase2-gpu-residual-design.md`
- `03-phase3-svg-residual-design.md`
- `07-post-phase6-residual-plan-2026-05-16.md`

## 入力

- `README.md`
- `scripts/generate_public_api_coverage.py`
- `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-core-effects-missing-triage.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-phase-7-residual-index.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-phase-7-triage-routing-index.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-phase-8-guarded-platform-index.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-phase-9-shortlist.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-phase-10-generator-polish-backlog.csv`
- `docs/plans/c-binding-remediation/06-public-api-coverage-roadmap.md`
- `docs/notes/bindings/public-api-coverage-matrix-progress-2026-05-06.md`
- `docs/notes/bindings/public-class-binding-candidate-survey-2026-05-06.md`
- `docs/notes/bindings/capi-and-handle-binding-coverage-survey-2026-05-06.md`

## 運用

- `public-api-coverage-matrix.csv` は生成物として扱い、手編集しない。
- 実装対象の確定や対象外判断は、triage CSV またはこの計画配下の追補文書で管理する。
- C API 追加後は `scripts/generate_public_api_coverage.py` で matrix を再生成し、configure/build と対象 smoke を実行する。
- optional module の API は、C API だけでなく CMake option、source registration、依存検出、テスト条件まで同じ作業単位で扱う。
- callback/global registration は `01-callback-global-registration-design.md` の方針に従う。Phase 5A で共通 foundation を作り、以後の provider / observer / guarded platform API でも同じ語彙を使う。
- Phase 6 完了後の残件は `07-post-phase6-residual-plan-2026-05-16.md` に従い、Phase 7 の triage refresh、Phase 8 の guarded platform/import-source、Phase 9 の optional module expansion、Phase 10 の coverage polish に分ける。
