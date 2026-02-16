# C Binding Remediation Plan

`skia/capi` と `skia/handles` の設計改善を、Rust利用前提で段階実施する計画セットです。

## 目的

- 所有権と解放規約を明確化し、`delete`/`ref/unref` の混在を解消する。
- `static` レジストリの安全性（無効キー、所有権破壊、スレッド安全性）を改善する。
- LuaJIT GC と Rust `Drop` の両方で安全に運用できる C API を整備する。
- 対象ファイルが多い前提で、修正漏れをゼロにする。

## 計画書一覧

- `00-objectives-and-constraints.md`
- `01-file-coverage-governance.md`
- `02-phase-1-registry-safety.md`
- `03-phase-2-ownership-api.md`
- `04-phase-3-rust-ffi-rollout.md`
- `05-phase-4-migration-and-cleanup.md`

## 管理ファイル

- `manifests/capi-files.txt`
- `manifests/handles-files.txt`
- `checklists/capi-status.csv`
- `checklists/handles-status.csv`

## 実施順

1. `01-file-coverage-governance.md` で対象確定・進捗管理を開始
2. `02-phase-1-registry-safety.md` を完了（安全化）
3. `03-phase-2-ownership-api.md` を完了（API規約固定）
4. `04-phase-3-rust-ffi-rollout.md` を完了（Rust層導入）
5. `05-phase-4-migration-and-cleanup.md` を完了（移行/整理）
