# 01 File Coverage Governance

## 目的

対象ファイル漏れを防ぎ、CMake改善の進捗を可視化する。

## 管理対象

- `manifests/reskia-cmake-files.txt`
- `checklists/cmake-status.csv`

## ステータス

- `todo`: 未着手
- `doing`: 実装中
- `blocked`: 保留
- `done`: 実装/レビュー/検証完了
- `na`: 今回対象外（理由を note に記載）

## 運用手順

1. マニフェスト更新

```bash
{ find cmake -type f -name '*.cmake' | sort; find . -maxdepth 2 -name 'CMakeLists.txt' | sort; } | sed 's#^\\./##' | sort -u > docs/plans/cmake-remediation/manifests/reskia-cmake-files.txt
```

2. チェックリスト更新

```bash
awk 'BEGIN{print "file,status,phase,owner,note"} {print $0",todo,,,"}' docs/plans/cmake-remediation/manifests/reskia-cmake-files.txt > docs/plans/cmake-remediation/checklists/cmake-status.csv
```

3. フェーズ完了判定

```bash
awk -F, 'NR>1 && $2!="done" && $2!="na" {c++} END {print c+0}' docs/plans/cmake-remediation/checklists/cmake-status.csv
```

## 品質ゲート

- フェーズ終了時に未完了件数 0
- `blocked/na` は必ず `note` 記載
