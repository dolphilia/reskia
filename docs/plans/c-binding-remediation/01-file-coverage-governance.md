# 01 File Coverage Governance

## 目的

対象ファイル数が多いため、修正漏れを防ぐ運用を先に固定する。

## 管理対象

- `manifests/binding-files.txt`（`skia/binding` の `*.cpp` / `*.h`）
- `manifests/static-files.txt`（`skia/static` の `*.cpp` / `*.h` / `*-internal.h`）
- `checklists/binding-status.csv`
- `checklists/static-status.csv`

## ステータス定義

- `todo`: 未着手
- `doing`: 実装中
- `blocked`: ブロック中
- `done`: 実装/レビュー/検証完了
- `na`: 対象外（理由を note に記載）

## 実行手順

1. マニフェスト再生成

```bash
find skia/binding -maxdepth 1 -type f \( -name '*.cpp' -o -name '*.h' \) | sort > docs/plans/c-binding-remediation/manifests/binding-files.txt
find skia/static -maxdepth 1 -type f \( -name '*.cpp' -o -name '*.h' -o -name '*-internal.h' \) | sort > docs/plans/c-binding-remediation/manifests/static-files.txt
```

2. チェックリスト初期化（初回のみ）

```bash
awk 'BEGIN{print "file,status,phase,owner,note"} {print $0",todo,,,"}' docs/plans/c-binding-remediation/manifests/binding-files.txt > docs/plans/c-binding-remediation/checklists/binding-status.csv
awk 'BEGIN{print "file,status,phase,owner,note"} {print $0",todo,,,"}' docs/plans/c-binding-remediation/manifests/static-files.txt > docs/plans/c-binding-remediation/checklists/static-status.csv
```

3. 変更単位で `status/phase/note` を更新

4. 各フェーズ完了時に差分検査

```bash
awk -F, 'NR>1 && $2!="done" && $2!="na" {c++} END {print c+0}' docs/plans/c-binding-remediation/checklists/binding-status.csv
awk -F, 'NR>1 && $2!="done" && $2!="na" {c++} END {print c+0}' docs/plans/c-binding-remediation/checklists/static-status.csv
```

## 品質ゲート

- フェーズを閉じる条件:
  - 対象フェーズのファイルが全て `done` または `na`
  - `na` の理由が `note` に記録済み
  - フェーズ検証コマンドが成功

## 担当粒度

- 1 PR あたり最大 25 ファイル目安
- `binding` と `static` を同時に跨ぐ変更は必ずテストを付ける
- 影響範囲が広い変更（所有権規約、ハンドル形式）は専用PRに分離
