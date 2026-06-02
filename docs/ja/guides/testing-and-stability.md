# Testing and Stability Guide

この文書は、Reskia の build / smoke / stability 確認の基本方針をまとめます。

C API の個別安全性規約は `docs/ja/guides/c-api-safety-guidelines.md` を参照してください。

## 目的

Reskia では、C ABI 境界、依存解決、optional feature、platform 差分が主な不安定要因になります。

安定性確認の目的:

1. `reskia` 本体が標準構成で build できる。
2. C API が invalid input で crash しない。
3. handle API が invalid / stale handle を安全に扱う。
4. optional feature が依存不足時に明確に無効化または skip される。
5. upstream Skia 追従時に coverage regression と stale C API を検出する。

## 標準 build

文書や CMake だけの変更でも、可能な範囲で configure / build を確認します。

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

依存や source list に関わる変更では、`source` mode も確認します。

```bash
cmake -S skia -B skia/cmake-build-source-local \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source-local -j 8
```

## Tests

テストは `RESKIA_BUILD_TESTS=ON` で有効化します。

```bash
cmake -S skia -B skia/cmake-build-tests \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests -j 8
ctest --test-dir skia/cmake-build-tests --output-on-failure
```

optional feature の test は、対応する feature flag と依存が揃った場合だけ登録されます。依存不足時は、未登録または明確な skip として扱います。

## C API Smoke

C API を変更したら、対象 API のリスクに応じて smoke を追加します。

優先して確認するもの:

- NULL receiver。
- required pointer NULL。
- invalid handle。
- stale handle。
- invalid rowBytes / buffer。
- factory failure。
- borrowed pointer lifetime。
- callback NULL no-op。
- callback context の扱い。
- returned handle の delete / release。

すべてのケースを毎回追加する必要はありません。変更した API の規約に対応する最小ケースを選びます。

## Coverage Gate

public API coverage に関わる変更では、coverage generator を実行します。

```bash
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream \
  --output docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv
```

`missing` / `deferred` / `partial` / `overcovered` は 0 を維持することを基本にします。stale report は header のみが望ましい状態です。

## Feature Flag Gate

feature flag を変更した場合は、次を確認します。

- configure 時に必要な dependency が検出されるか。
- dependency 不足時に明確に無効化されるか。
- unsupported platform で分かりやすく失敗するか。
- optional test が依存不足時に誤って登録されないか。

代表例:

- `RESKIA_ENABLE_GPU_METAL=ON` は Apple 環境が必要。
- `RESKIA_ENABLE_GPU_DAWN=ON` は Graphite が必要。
- text stack は HarfBuzz、ICU、ICU4X、libgrapheme、CoreText の有無で縮退する。

## Sanitizer

メモリ所有権、callback、borrowed pointer、buffer を触る変更では、可能なら sanitizer build を追加で確認します。

例:

```bash
cmake -S skia -B skia/cmake-build-asan \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON \
  -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined" \
  -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" \
  -DCMAKE_SHARED_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build skia/cmake-build-asan -j 8
ctest --test-dir skia/cmake-build-asan --output-on-failure
```

環境により sanitizer と prebuilt dependency の組み合わせで追加調整が必要になる場合があります。その場合は、失敗条件を記録します。

## 変更種別ごとの最小確認

| 変更種別 | 最小確認 |
| --- | --- |
| docs only | `git diff --check`、必要に応じて標準 build。 |
| CMake source list | configure / build。feature flag 変更なら該当 mode も確認。 |
| C API header / implementation | build、対象 smoke、coverage matrix。 |
| handles | invalid / stale handle smoke。 |
| upstream Skia sync | candidate coverage、stale report、build / smoke、lock update 後の再確認。 |
| dependency script | `bootstrap_third_party.sh` / `build_third_party.sh` の対象 mode 確認。 |

## 関連文書

- `docs/ja/guides/cmake-migration-guide.md`
- `docs/ja/guides/c-api-safety-guidelines.md`
- `docs/ja/guides/public-api-coverage-workflow.md`
- `docs/ja/guides/skia-upgrade-workflow.md`
