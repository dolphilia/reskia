# 32 Phase 2 Batch AE: picture / picture recorder C API safety

作業開始日時: 2026-05-10 00:22:04 JST

## 目的

Phase 2 の次バッチとして、`SkPicture` / `SkPictureRecorder` 周辺を fail-safe に寄せる。picture は nullable `sk_sp` factory、serialize/deserialize、shader 生成を扱い、recorder は borrowed recording canvas と finish 時の nullable handle を扱うため、NULL 入力・生成不能・必須 pointer 欠落を C ABI 境界で明示する。

対象:

- `skia/capi/sk_picture.h`
- `skia/capi/sk_picture.cpp`
- `skia/capi/sk_picture_recorder.h`
- `skia/capi/sk_picture_recorder.cpp`

## 実装変更

各 C API に NULL ガード、enum 値チェック、nullable handle helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_picture_t`, `sk_shader_t`, `sk_data_t`, `sk_rect_t`, `sk_drawable_t`) | `0` |
| borrowed canvas pointer | `NULL` |
| id / size / count | `0` |
| `bool` query | `false` |
| playback / serialize-to-stream / ref-count mutation / delete | no-op |

nullable `sk_sp` は handle table に登録せず、C ABI では handle `0` として返す。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `SkPicture_playback`: `canvas` は非 NULL。callback は NULL 許可。
- `SkPicture_serialize`: serial procs は NULL 許可。
- `SkPicture_serializeToStream`: stream は非 NULL。
- `SkPicture_makeShader`: local matrix / tile rect は NULL 許可。tile mode / filter mode は既知範囲内。
- `SkPicture_MakeFromStream`: stream は非 NULL。
- `SkPicture_MakeFromData`: data は非 NULL。
- `SkPicture_MakeFromMemory`: data は非 NULL、size は `> 0`。
- `SkPictureRecorder_beginRecording`: bounds は非 NULL。戻り値は borrowed canvas。
- `SkPictureRecorder_beginRecordingWithSizeAndFactory`: width / height は `>= 0`。factory は NULL 許可。
- `SkPictureRecorder_getRecordingCanvas`: NULL 入力や未 recording では `NULL`。戻り値は borrowed canvas。
- `finishRecording*`: NULL recorder や生成不能では handle `0`。

## smoke test

`test_picture_recorder_invalid_input_smoke` を追加し、`ctest` に `c_skia_picture_recorder_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkPicture` query/refcount/serialize/shader APIs が fail-safe 値または no-op になる。
- static factory の NULL data / empty memory が handle `0` になる。
- placeholder picture の unique id、cull rect、shader 生成を確認する。
- NULL `SkPictureRecorder` と invalid size が fail-safe になる。
- valid recording flow で borrowed canvas を取得し、picture handle を finish できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_picture_recorder_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_picture_recorder_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_picture_recorder_invalid_input_smoke` build 成功。
- `c_skia_picture_recorder_invalid_input_smoke` 成功。
- test build 時に Skia private header 由来の C++17 inline variable 警告が出たが、リンクと実行は成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_picture.h`
- `skia/capi/sk_picture.cpp`
- `skia/capi/sk_picture_recorder.h`
- `skia/capi/sk_picture_recorder.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFontMgr` / font family enumeration 周辺
- `SkTypeface_Mac` の Apple 限定 C API
- `SkFontMgrFontConfig` 周辺
