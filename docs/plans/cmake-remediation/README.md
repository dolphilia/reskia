# CMake Remediation Plan

Reskia の CMake 構成を「変更しやすく、壊れにくく、追跡しやすい」状態へ改善する計画です。

## 対象

- `cmake/deps/ReskiaDeps.cmake`
- `skia/CMakeLists.txt`
- `skcms/CMakeLists.txt`
- `skpath/CMakeLists.txt`
- `skresources/CMakeLists.txt`
- `svg/CMakeLists.txt`
- `third_party/CMakeLists.txt`

## 計画書

- `00-objectives-and-constraints.md`
- `01-file-coverage-governance.md`
- `02-phase-1-low-risk-cleanup.md`
- `03-phase-2-modularization.md`
- `04-phase-3-dependency-matrix-and-ci.md`
- `05-phase-4-rollout-and-deprecation.md`

## 管理ファイル

- `manifests/reskia-cmake-files.txt`
- `checklists/cmake-status.csv`

## 実施順

1. 対象固定と進捗管理を開始
2. 低リスクの整備（命名・`project()`・グローバル設定削減）
3. `skia/CMakeLists.txt` の分割
4. 依存モード/プラットフォーム行列の明確化と CI 反映
5. 移行完了後の互換整理
