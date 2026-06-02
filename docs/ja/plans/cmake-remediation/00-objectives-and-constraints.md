# 00 Objectives and Constraints

## 目的

- 巨大化した `skia/CMakeLists.txt` の責務分離
- CMake をターゲット指向へ寄せ、グローバル副作用を削減
- 依存解決モード（`prebuilt/source/system`）を運用しやすく明文化
- 将来の Skia 追従時に差分管理しやすい構造へ移行

## 成果物

- 分割済み CMake モジュール
- モード/OS サポート表
- 最低限の CI 検証行列
- 互換ポリシー（既存運用からの移行ルール）

## 制約

- 既存ビルド手順は段階移行し、即時破壊しない
- 1PRあたりの責務を限定する
- 機能追加と構成整理を同時に混ぜない

## 受け入れ基準

- `skia/CMakeLists.txt` はエントリ + include 中心まで縮小
- `include_directories/link_directories` の新規追加禁止
- 主要 7 ファイルが `checklists/cmake-status.csv` で `done`
- `prebuilt/source` の configure 成功を維持
