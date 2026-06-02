# vendor

比較・参照用の Skia ソース取得先を管理するディレクトリです。

- `skia-source.lock`: 取得元 URL と固定コミットを管理するロックファイル（追跡対象）
- `skia-upstream/`: 比較・参照用の実クローン（`.gitignore` で追跡対象外）

現在の baseline:

- `SKIA_REF=70f9d90bc8e6a56101d036153cfef28088e57f5b`
- `SKIA_BASELINE_DATE=2026-06-01`

取得・更新は以下を使います。

```bash
scripts/fetch_skia_upstream.sh
```

段階的アップグレードでは、probe と verification が完了するまで `skia-source.lock` を更新しません。候補 commit は固定 hash として扱い、floating `main` を baseline にしないでください。

関連文書:

- `docs/plans/skia-incremental-upgrade/`
- `docs/notes/skia-incremental-upgrade-readiness-2026-05-22.md`
