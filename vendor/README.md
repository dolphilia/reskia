# vendor

比較・参照用の Skia ソース取得先を管理するディレクトリです。

- `skia-source.lock`: 取得元 URL と固定コミットを管理するロックファイル（追跡対象）
- `skia-upstream/`: 比較・参照用の実クローン（`.gitignore` で追跡対象外）

取得・更新は以下を使います。

```bash
scripts/fetch_skia_upstream.sh
```
