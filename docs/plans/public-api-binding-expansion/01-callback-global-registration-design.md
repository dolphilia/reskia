# Callback / Global Registration Design Note

- 作成日: 2026-05-14
- 作業開始時刻: 2026-05-14 17:58:50 JST
- 対象: C callback と Skia global registration API の C ABI 方針

## 結論

Phase 1 では実装しない。Phase 1 では callback/global registration を「設計待ち real_gap」として残し、所有権と lifetime の原則だけを固定する。

実装は `Phase 5A: Callback / Resource Provider Foundation` としてまとめて行う。実行位置は Phase 3 の SVG DOM 最小公開後、Phase 5 の skottie / skresources / sksg resource provider と observer API に入る前とする。

この順序にする理由は、`SkGraphics::SetImageGeneratorFromEncodedDataFactory` と `SkTypeface::Register` が単発 API ではなく、skresources、skottie、SVG resource provider、font factory、observer callback と同じ ABI 問題を共有するためである。

2026-05-15 に Phase 5A を開始し、最初の concrete API として `SkGraphics::SetImageGeneratorFromEncodedDataFactory` を実装した。`reskia_callback_release_proc_t` を共通 typedef として追加し、登録 context は `shared_ptr` で保持する。登録置換時には旧 context を release するが、callback 実行中の context は callback 終了まで生存する。

## Phase 1 で残す対象

- `SkGraphics::SetImageGeneratorFromEncodedDataFactory`
- `SkTypeface::Register`

どちらも global state に C callback を登録する。登録後の callback lifetime、`void *user_data` の所有者、戻り値の所有権、解除可否、threading 前提が未定義のまま実装すると、後続 module と規約が割れる。

## Phase 5A でまとめる対象

Phase 5A では、callback / provider / registration の共通 ABI を先に作り、その上に具体 API を載せる。

実装候補:

- `SkGraphics::SetImageGeneratorFromEncodedDataFactory`
- `SkTypeface::Register`
- skresources image/data/font resource provider
- skottie resource provider
- skottie property observer / text property callback
- SVG DOM resource provider が必要になった場合の provider hook

Phase 5A は Phase 3 完了後に着手する。Phase 3 では `SkSVGDOM::MakeFromStream`、`render`、`setContainerSize` などの non-callback API を先に公開し、resource provider hook は Phase 5A まで保留する。

## C ABI 原則

callback API は原則として次の形に寄せる。

```c
typedef void *reskia_callback_context_t;

typedef void (*reskia_callback_release_proc_t)(void *user_data);
```

個別 callback は `void *user_data` を最後の引数に置く。

```c
typedef sk_some_handle_t (*reskia_some_callback_t)(
    const reskia_input_t *input,
    void *user_data);
```

登録 API は callback と context を分けて受け取る。

```c
bool ReskiaSomeRegistry_setCallback(
    reskia_some_callback_t callback,
    void *user_data,
    reskia_callback_release_proc_t release_proc);
```

## 所有権ルール

- callback function pointer は caller が process lifetime 以上に有効に保つ。
- `user_data` は登録成功後、Reskia 側が保持する。
- `release_proc` が非 NULL の場合、登録置換または shutdown 相当のタイミングで Reskia 側が一度だけ呼ぶ。
- `release_proc` が NULL の場合、`user_data` は borrowed とみなし Reskia は解放しない。
- callback が返す handle は caller-owned / transferred のどちらかを API コメントで明示する。
- callback から `0` / `NULL` が返った場合は failure として扱い、Skia 側には null result を渡す。

## Global Registration ルール

global registration は原則として初期化時に呼ぶ API とする。

- thread-safe な再登録を保証しない。
- 登録済み callback の置換は可能にするが、置換時に旧 `release_proc` を呼ぶ。
- Skia 側に deregistration API がない場合、Reskia 側でも完全解除は提供しない。
- 完全解除できない API は `clear` ではなく `replace` のみを提供する。
- process lifetime に残る global hook は header コメントと計画書に明記する。

## 型別方針

`SkGraphics::SetImageGeneratorFromEncodedDataFactory`:

- 実装済み。
- 入力は callback 中だけ有効な borrowed `const_sk_data_t` として C ABI に渡す。
- callback は transferred `sk_image_generator_t` handle を返す。`0` を返した場合は failure ではなく Skia の default encoded-data decoder へ fallback する。
- Skia 側に deregistration API がないため、完全解除は提供しない。custom 生成を止める場合は `0` を返す callback で置換する。

`SkTypeface::Register`:

- 入力の `std::unique_ptr<SkStreamAsset>` は C ABI では transferred stream asset wrapper として渡す。
- callback は `sk_typeface_t` または owned typeface wrapper を返す。
- stream asset を callback 後も保持できるかどうかを API コメントで明示する。初期方針は callback 内だけ有効な owned transfer とし、保持が必要なら callback 側が明示的に clone/copy する。
- 未実装。次に扱う場合は `FactoryId` の C ABI 表現と、登録解除不能な global font factory の置換ルールを `SkGraphics` と同じ語彙で揃える。

## Phase 5A progress 2026-05-15

追加済み:

- `reskia_callback_release_proc_t`
- `reskia_image_generator_from_encoded_data_factory_t`
- `SkGraphics_SetImageGeneratorFromEncodedDataFactory`

検証済み:

- callback が borrowed `const_sk_data_t` を受け取ること。
- callback が `0` を返した場合、生成結果は失敗しつつ Skia fallback path に委ねられること。
- 登録置換時に旧 context の `release_proc` が一度だけ呼ばれること。
- `NULL` callback は登録を置換せず、既存 context も release しないこと。

残作業:

- `SkTypeface::Register`
- skresources provider bridge
- skottie resource provider / property observer
- GPU finished proc / upload callback など Phase 2 で保留した callback API

## 受け入れ条件

Phase 5A の完了条件:

- callback context の release が smoke で一度だけ検証される。
- callback が `NULL` を返す failure path を smoke で検証する。
- registration 置換時の旧 context release を smoke で検証する。
- global hook が解除不能な場合、その制約を header と計画書に明記する。
- `SkGraphics`、`SkTypeface`、skresources/skottie provider の callback 規約が同じ文法で説明できる。

## Phase 1 での扱い

Phase 1 の core/effects triage では、対象 2 件を `real_gap` のまま残す。ただし note には `Phase 5A callback/global registration foundation` で実装することを明記する。

これにより、coverage 上は未実装であることを維持しつつ、Phase 1 の実装対象から外す理由と次の実装段階を追跡できる。
