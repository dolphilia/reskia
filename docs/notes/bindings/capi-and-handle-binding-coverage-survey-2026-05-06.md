# Reskia C API / Handle Binding Coverage Survey

- 作成日時: 2026-05-06
- 作業開始時刻: 2026-05-06 15:38:23 JST
- 対象: `skia/capi`, `skia/handles`, `cmake/reskia/sources-capi.cmake`, `docs/plans/c-binding-remediation/checklists`

## 要約

Reskia の C API バインディングは、Skia の公開クラスについて「公開メソッドと static factory/helper を可能な限り C ABI に露出する」方針で進められていると見てよい。特に `SkBitmap`, `SkImage`, `SkPath` は単なる最小ラッパーではなく、constructor/copy/delete、主要 getter/setter、factory、overload 別の意味名 API、戻り値オブジェクトの handle 化、RefCounted 型の retain/release まで広く整備されている。

一方で、網羅性はまだ「全型完了」ではない。`docs/plans/c-binding-remediation/checklists/capi-status.csv` には多くの C API が `todo,P2` として残っており、型安全性、所有権表現、命名整理、ABI として危うい引数の置き換えは継続課題である。代表例では `SkImage_imageInfo` と async read 系が未実装/TODO、`SkPath` には `std::initializer_list` 由来の `void*` 受け API が残る。

## 調査範囲と規模感

`skia/capi` はポインタ系 C API、`skia/handles` は整数 handle 系 API を担当する。調査時点の概算は次の通り。

- `skia/capi/*.h`: 161 ファイル
- `skia/capi/*.cpp`: 160 ファイル
- `skia/capi/*.h` の関数宣言らしきもの: 約 2807 件
- `skia/handles/static_*.cpp`: 109 ファイル

関数数が特に多い C API ヘッダは次の通り。

| Header | 関数数 |
| --- | ---: |
| `sk_canvas.h` | 126 |
| `sk_matrix.h` | 110 |
| `sk_path.h` | 108 |
| `reskia_ffi.h` | 99 |
| `sk_bitmap.h` | 84 |
| `sk_string.h` | 67 |
| `sk_rect.h` | 66 |
| `sk_read_buffer.h` | 66 |
| `sk_paint.h` | 57 |
| `sk_path_builder.h` | 54 |
| `sk_pixmap.h` | 53 |
| `sk_image.h` | 48 |
| `sk_font.h` | 47 |

この規模から、Reskia は少数の描画エントリだけを公開するプロジェクトではなく、Skia の主要型を C ABI から再利用できる面を広く作るプロジェクトとして設計されている。

## C API バインディングの基本形

`skia/capi` の実装は、おおむね次の形を取る。

1. C 側には `reskia_*_t` または `sk_*_t` 系の不透明型を見せる。
2. `.cpp` 側で `As*`/`To*`/`from_capi` 系の変換を通して Skia C++ 型へ戻す。
3. C++ メソッドを直接呼び出し、戻り値を C ABI で表現できる値、ポインタ、不透明 wrapper、または handle に変換する。
4. `sk_sp<T>` などの RefCounted 型は `release`/`ref`/`unref`、または `reskia_ffi` の retain/release wrapper で寿命を管理する。
5. 値型の戻り値は `static_*_make` で整数 handle 化して返す場合が多い。

overload は `_2`, `_3` のような連番ではなく、`withInfoRowBytes` や `withRectSampling` のような意味名へ整理する流れにある。`docs/plans/c-binding-remediation/checklists/phase4-sequential-api-rename-status.csv` では、`SkBitmap` や `SkImage` 周辺の連番 API の多くが rename 済みになっている。

## 代表例: SkBitmap

対象ファイル:

- `skia/capi/sk_bitmap.h`
- `skia/capi/sk_bitmap.cpp`

`SkBitmap_` API は 84 件あり、`SkBitmap` の公開面をかなり厚く追っている。

主な公開範囲:

- 生成/破棄: default constructor, copy constructor, delete
- 代入/交換: copy, swap
- 画像情報: width, height, dimensions, bounds, rowBytes, colorType, alphaType, colorSpace, imageInfo
- pixel 管理: setInfo, setPixels, allocPixels 系, tryAllocPixels 系, installPixels 系
- 参照/共有: getPixels, getAddr, pixmap, peekPixels, reset
- 描画/変換: erase 系, readPixels/writePixels, extractSubset
- shader 化: makeShader 系
- immutable/opaque 判定: setImmutable, isImmutable, computeByteSize, isNull, drawsNothing
- static helper: `SkBitmap_ComputeIsOpaque`

戻り値の扱いは混在している。`SkBitmap` 自体は `static_sk_bitmap` handle を持たず、`reskia_bitmap_t*` として C API 層で所有される。一方で、戻り値が `SkImage`, `SkIRect`, `SkISize`, `SkShader`, `SkPixmap`, `SkColorSpace` などになる場合は、それぞれ `static_sk_image_make` などで handle 化して返す。

このため `SkBitmap` は「ポインタ系 C API を主軸にしつつ、周辺型の戻り値だけ handle 化する」代表例である。全体としては網羅志向だが、`docs/plans/c-binding-remediation/checklists/capi-status.csv` 上では `sk_bitmap` はまだ `todo,P2` であり、所有権注釈や API 形状の最終整理は残る。

## 代表例: SkImage

対象ファイル:

- `skia/capi/sk_image.h`
- `skia/capi/sk_image.cpp`
- `skia/handles/static_sk_image.h`
- `skia/handles/static_sk_image-internal.h`
- `skia/handles/static_sk_image.cpp`

`SkImage_` API は 48 件あり、`SkImage` の instance method と static factory を広く公開している。

主な公開範囲:

- 参照管理: release, ref, unref
- 基本情報: width, height, dimensions, bounds, uniqueID, alphaType, colorType, colorSpace
- 状態判定: isAlphaOnly, isOpaque, isTextureBacked, isValid
- 読み出し: peekPixels, readPixels 系, scalePixels
- 変換: makeShader 系, makeSubset 系, makeColorSpace 系, makeNonTextureImage, makeRasterImage
- encoded data: refEncodedData, encodeToData, encodeToDataWithContext
- static factory: RasterFromBitmap, RasterFromData, RasterFromPixmapCopy, RasterFromPixmapRasterProc, TextureFromImage, DeferredFromEncodedData など
- GPU/Graphite 系 overload: recorder/context を受ける subset/colorSpace/colorTypeAndColorSpace API

未完了または保留されている主な API:

- `SkImage_imageInfo`: TODO
- `asyncRescaleAndReadPixels`
- `asyncRescaleAndReadPixelsYUV420`
- `asyncRescaleAndReadPixelsYUVA420`

`SkImage` の handle 実装は `HandleTable<sk_sp<SkImage>>` を使う。`static_sk_image_make` は `sk_sp<SkImage>` を table に move し、整数 handle を発行する。`borrow_entity` は `sk_sp` のコピーを返すため参照カウントが増える。`take_entity` は table から取り出す。`get_ptr` は table 内の `sk_sp` から生ポインタを返す。

この構造により、C API から返された `SkImage` は整数 handle として安全に運べる一方、`reskia_ffi` 側では safe wrapper 向けに retain/release/borrow が別途提供される。

## 代表例: SkPath

対象ファイル:

- `skia/capi/sk_path.h`
- `skia/capi/sk_path.cpp`
- `skia/handles/static_sk_path.h`
- `skia/handles/static_sk_path.cpp`

`SkPath_` API は 108 件あり、今回見た中でも特に網羅性が高い。

主な公開範囲:

- 生成/破棄: default/copy/move 相当, delete
- 状態取得: isInterpolatable, isFinite, isVolatile, isLastContourClosed, countVerbs, countPoints, getBounds, computeTightBounds
- path 変更: moveTo, lineTo, quadTo, conicTo, cubicTo, close, reset, rewind
- shape 追加: addRect, addOval, addCircle, addArc, addRRect, addPoly, addPath
- 変換/簡約: transform, offset, reverseAddPath, toggleInverseFillType
- iterator/raw access: getPoint, getPoints, getVerbs
- 補間/包含: interpolate, contains, isRect, isOval, isRRect
- static factory/helper: Make, Rect, Oval, Circle, RRect, Polygon, Line, IsLineDegenerate, IsQuadDegenerate, IsCubicDegenerate, ConvertConicToQuads など

`SkPath_interpolate` は `reskia_status_t` を返し、null 入力を検出する形になっている。これは単に C++ メソッドを薄く呼ぶだけでなく、C ABI から利用する際の失敗表現を整えようとしている例である。

一方で、C ABI として整理が必要な API も残る。`SkPath_addPolyFromList` や `SkPath_PolygonFromList` は `std::initializer_list` に由来する引数を `void*` として受けており、言語間 FFI では安全に使いにくい。将来的には `points + count` 形式へ寄せるのが自然である。

`SkPath` の handle 実装は `HandleTable<SkPath>` を使う。`SkPath` は値型なので table 内にコピー保持され、`get_entity` もコピーを返す。`get_ptr` は table 内の値のアドレスを返す。`SkImage` のような refcount 所有ではなく、値型 handle として管理される点が違う。

## HandleTable の実装構造

対象ファイル:

- `skia/handles/handle_table.hpp`

handle 系 API は `HandleTable<T>` にほぼ集約されている。実装上の特徴は次の通り。

- `std::mutex` で table 操作を直列化する。
- `std::map<uint32_t, T>` に slot ごとの値を保持する。
- `std::set<uint32_t>` で空き slot を管理する。
- `std::vector<uint32_t> generations_` で世代番号を保持する。
- handle は 20 bit slot と generation を組み合わせた 31 bit 正整数として発行される。
- `erase` 時に generation を進め、古い handle を stale として弾けるようにする。
- 無効 handle は `get_ptr` なら `nullptr`、`contains` なら `false`、`take_or_default` なら default 値になる。

この設計により、単純な連番 ID よりも use-after-free 由来の stale handle 誤用を検出しやすい。ただし、`get_ptr` で table 内アドレスを返した後の寿命は呼び出し側の規約に依存するため、長期保持しない前提を API 文書側にも明確に残す必要がある。

## reskia_ffi の役割

対象ファイル:

- `skia/capi/reskia_ffi.h`
- `skia/capi/reskia_ffi.cpp`

`reskia_ffi` は、Rust などの safe wrapper から扱いやすい所有権 API をまとめる橋渡し層である。

主な役割:

- RefCounted 型に対する `reskia_*_retain`, `reskia_*_release`, `reskia_*_borrow_from_handle`
- 値型に対する clone/delete
- borrowed API の明示化
- handle から pointer wrapper への変換

RefCounted 型の wrapper は `RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER` macro で定義される。`SkImage`, `SkSurface`, `SkShader`, `SkData` などに適用されており、handle table から取り出した `sk_sp<T>` を safe wrapper 側の参照管理へつなぐ設計になっている。

値型の `Paint` や `Path` は refcount ではなく clone new/delete 方式で扱われる。borrowed API には `reskia_surface_borrow_canvas`, `reskia_*_borrow_pixels`, stream peek 系などが含まれ、所有権を渡さない返却であることを名前で表そうとしている。

## CMake 上の組み込み

対象ファイル:

- `cmake/reskia/sources-capi.cmake`

多くの `skia/capi/*.cpp` は常時ソースに含まれる。機能依存があるものは CMake option によって条件付きで追加される。

主な条件付き C API:

- `RESKIA_ENABLE_AVIF`
- `RESKIA_ENABLE_JPEGXL`
- `RESKIA_ENABLE_GIF`
- `RESKIA_ENABLE_RAW`
- `RESKIA_ENABLE_JPEG_ENCODER`
- `RESKIA_ENABLE_WEBP_ENCODER`
- `RESKIA_ENABLE_PDF`
- `RESKIA_ENABLE_SKPARAGRAPH`
- `RESKIA_ENABLE_SKOTTIE`
- `RESKIA_ENABLE_SKSG`
- `RESKIA_ENABLE_FONTCONFIG_CAPI`

このため、C API の網羅性は単にファイルがあるかだけでなく、ビルドオプションと依存ライブラリの有無にも左右される。

## 既存の進捗管理

`docs/plans/c-binding-remediation/checklists` には、C API 整備の進捗管理ファイルがある。

重要なチェックリスト:

- `phase2-type-classification.md`
- `phase2-release-api-status.csv`
- `phase4-sequential-api-rename-status.csv`
- `static-handle-table-status.csv`
- `capi-status.csv`

`phase2-type-classification.md` の集計では RefCounted 28 型、NonRefCounted 93 型、Borrowed API 17 件が分類済み。`phase2-release-api-status.csv` では RefCounted 28 型の delete/unref 統一などが done になっている。`static-handle-table-status.csv` ではほぼ全 `static_*.cpp` が `HandleTable` 移行完了であり、`static_sk_color.cpp` と `static_sk_image_read_pixels_callback.cpp` は API 未定義/コメントアウトにより `na` とされている。

一方で、`capi-status.csv` には `todo,P2` が多く残る。つまり、handle table と RefCounted release API の基盤整備はかなり進んでいるが、全 C API の細部レビューは継続中である。

## 網羅性の評価

現時点の評価は次の通り。

| 観点 | 評価 |
| --- | --- |
| 主要 Skia 型の C API 露出 | 高い |
| 公開 method/static method の追従方針 | 強い |
| overload の意味名整理 | 進行済み、主要例はかなり完了 |
| RefCounted 型の寿命管理 | 基盤は整備済み |
| 値型 handle 管理 | `HandleTable<T>` へかなり移行済み |
| C ABI としての完成度 | 型によって差がある |
| safe wrapper 向け所有権 API | `reskia_ffi` で整備中 |
| 未実装/TODO の残量 | まだ残る |

結論として、Reskia のバインディングは「必要最小限」ではなく「公開 API をできるだけ全面的に C API 化する」方向で進んでいる。ただし、Skia 全体の API 面積が大きいため、網羅性と ABI 品質の両方を同時に完了するには、チェックリスト駆動の継続作業が必要である。

## 今後のタスク候補

優先度が高い順に、次の作業が妥当である。

1. `capi-status.csv` の `todo,P2` を型ごとに減らす
   - まず `SkBitmap`, `SkImage`, `SkPath` の代表型から、所有権、null 安全性、命名、ABI 互換性を再確認する。

2. C ABI として危うい API を置き換える
   - `std::initializer_list` 由来の `void*` API は、`pointer + count` 形式の明示 API へ寄せる。

3. TODO/commented API の扱いを決める
   - `SkImage_imageInfo` と async read 系は、未実装のまま残すのか、callback/ownership API を設計して実装するのかを決める。

4. `SkBitmap` の所有権モデルを明文化する
   - `SkBitmap` 自体は handle 化されていないため、`reskia_bitmap_t*` の所有権と、周辺戻り値 handle の所有権の違いを利用者向けに明示する。

5. `reskia_ffi` と `skia/capi` の役割分担を文書化する
   - C++ メソッドの薄い C API と、safe wrapper 向け所有権 API の境界を明確にする。

6. handle pointer borrow の寿命規約を文書化する
   - `get_ptr` が返す table 内 pointer を長期保持してよいかどうか、型ごとに扱いを明示する。

7. 代表型の API coverage 表を自動生成する
   - upstream Skia header の public method と `skia/capi` の対応関数を比較するスクリプトを作ると、網羅性の議論を手作業から機械的な差分管理へ移せる。

## 次に着手するなら

最初の具体タスクとしては、`SkImage_imageInfo` の実装可否確認と、`SkPath_addPolyFromList` / `SkPath_PolygonFromList` の C ABI 置換案作成がよい。どちらも今回の代表調査で見えた未完了箇所であり、影響範囲が比較的局所的で、C API 品質を上げる効果が大きい。
