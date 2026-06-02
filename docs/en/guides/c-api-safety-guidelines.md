# Reskia C API Safety Guidelines

This document defines safety rules for editing `skia/capi`, `skia/handles`, and `skia/test`.

The goal is to keep C API misuse from crashing callers and to make ownership and lifetime clear from the API surface.

## Principles

1. At the C ABI boundary, NULL, invalid handles, stale handles, and out-of-range values must not crash.
2. Do not change the meaning of Skia C++ APIs; normalize validation and failure values on the C API side.
3. Do not break existing ABI in bulk. Use compatibility wrappers, new API names, or migration phases when needed.
4. Return ownership and lifetime must be clear from header comments.
5. When hardening an API, add invalid-path and minimal valid-path smoke tests where practical.
6. Keep implementation, header comments, tests, coverage, and checklists aligned.

## Terms

| Term | Meaning | Caller responsibility |
| --- | --- | --- |
| `caller-owned` | Object, handle, or reference owned by the caller. | Call the matching `delete`, `release`, or `unref`. |
| `retained` | Refcount was increased and the result is caller-owned. | Call `release`. |
| `borrowed` | Lifetime depends on a parent object, handle table, or Skia internal storage. | Do not release it. Do not keep it past its lifetime. |
| `consumed` | Callee takes ownership of an argument. | Do not release it after passing it. |
| `required` | NULL is not allowed. | NULL produces a fail-safe value or no-op. |
| `optional` | NULL is meaningful and allowed. | NULL may be passed. |
| `callback-only` | Valid only during callback execution. | Do not store it outside the callback. |
| `not retained` | Callee does not retain the pointer. | Caller owns lifetime after the call. |

## Invalid Input Return Rules

NULL receivers, required pointer NULL, invalid handles, stale handles, out-of-range enums, invalid buffers / rowBytes, and count / array mismatches should follow these rules.

| API kind | Return on invalid input |
| --- | --- |
| `void` mutation / draw / setter | no-op |
| `bool` | `false` |
| integer handle return | `0` |
| raw borrowed pointer return | `NULL` |
| refcounted pointer return | `NULL` |
| numeric getter | usually `0` |
| enum getter | `0` equivalent unless compatibility requires otherwise |
| `delete` / `release` / `unref` | no-op |
| callback API | If callback is non-NULL, call it with a failure result. If callback is NULL, no-op. |

If an exception is needed, document the reason in the header comment and work record. If upstream Skia treats a NULL payload as meaningful, keep only the receiver required and mark the payload optional.

## Input Validation

### Receiver

The first receiver argument in method-like APIs is required.

```cpp
if (canvas == nullptr) {
    return;
}
```

For APIs with return values, follow the return rules.

```cpp
if (image == nullptr) {
    return 0;
}
```

### Pointer Input

Mark `const T*` inputs optional only when the Skia API allows NULL. Otherwise guard them as required.

```cpp
if (image == nullptr || sampling == nullptr) {
    return 0;
}
```

### Output Pointer

Output pointers are required by default. When NULL, return `false`, `0`, or no-op.

```cpp
if (font == nullptr || widths == nullptr) {
    return false;
}
```

If multiple out parameters are optional, say so in the header comment.

### Count and Array

If `count <= 0` can be treated as empty input, an array pointer may be NULL. If `count > 0`, the array is required.

```cpp
if (count < 0) {
    return;
}
if (count > 0 && values == nullptr) {
    return;
}
```

For unsigned counts such as `size_t`, treat `count > 0 && array == nullptr` as invalid.

### Handle

Validate integer handles through the registry or `has_*_handle` equivalent. Do not create missing or stale keys through `operator[]` style access.

```cpp
if (!has_image_handle(image)) {
    return;
}
```

Handle `0` is invalid by default. If an API treats `0` as empty input, document that in the header comment.

### Buffer and Row Bytes

Validate pixel buffers as a group: info, pixels, and rowBytes.

```cpp
if (info == nullptr || pixels == nullptr || !info->validRowBytes(rowBytes)) {
    return false;
}
```

If a caller-owned buffer is not retained by the callee, write `not retained`. If bitmap, pixmap, or canvas storage is borrowed, document which object owns the lifetime.

## Ownership and Lifetime

### Handle Return APIs

Successful handle returns are `caller-owned`. Return `0` for factory failure or invalid input.

```c
/**
 * image and sampling are required.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * Returns 0 on invalid input or factory failure.
 */
sk_shader_t SkImage_makeShader(...);
```

### Borrowed Pointer Returns

The caller must not release borrowed pointers. Always document the owning object or storage.

```c
/**
 * Returns a borrowed canvas owned by surface.
 * The returned pointer must not be deleted by the caller.
 * Returns NULL when surface is NULL.
 */
reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface);
```

### RefCounted

For RefCounted objects, prefer `retain` / `release` as the standard rule. Compatibility `delete` APIs may remain, but should delegate internally to release-like behavior.

Header comments should say `caller-owned reference` and name the release function.

### Callback

Result and pointer values passed to callbacks are normally `callback-only`. They must not be stored outside the callback.

The context pointer is caller-owned. Reskia does not release it.

For invalid input:

- Non-NULL callback: call it with a failure result or `NULL result`.
- NULL callback: no-op.
- NULL context: allowed.

## Header Comments

APIs with safety rules should have a short `/** ... */` comment immediately before the declaration.

Include:

- required input
- optional input
- returned ownership
- borrowed lifetime
- consumed ownership
- callback result / context lifetime
- failure value
- count and array relationship
- buffer / rowBytes / storage lifetime
- delete / release method

A simple NULL no-op can remain as an end-of-line comment.

```c
void SkCanvas_delete(reskia_canvas_t *canvas); // NULL canvas is no-op.
```

Preferred vocabulary:

- `required`
- `may be NULL`
- `optional out param`
- `caller-owned`
- `borrowed`
- `not retained`
- `valid only while ... remains unchanged`
- `callback-only`
- `invalid input is no-op`
- `returns 0 on invalid input or factory failure`
- `returns false on invalid input`

Avoid:

- vague words such as `safe`
- `owned` without an owner
- behavior that is not guaranteed by implementation or smoke tests
- overly long prose

New safety comments should use short English sentences. Existing comments do not need bulk translation.

## Implementation Patterns

### `void` API

```cpp
void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top) {
    if (canvas == nullptr || !has_image_handle(image)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), left, top);
}
```

### `bool` API

```cpp
bool SkImage_readPixelsWithImageInfo(
        reskia_image_t *image,
        const reskia_image_info_t *dstInfo,
        void *dstPixels,
        size_t dstRowBytes) {
    if (image == nullptr || dstInfo == nullptr || dstPixels == nullptr ||
        !reinterpret_cast<const SkImageInfo *>(dstInfo)->validRowBytes(dstRowBytes)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(
            *reinterpret_cast<const SkImageInfo *>(dstInfo),
            dstPixels,
            dstRowBytes,
            0,
            0);
}
```

### Handle Return API

```cpp
sk_shader_t SkImage_makeShader(
        reskia_image_t *image,
        reskia_image_tile_mode_t tmx,
        reskia_image_tile_mode_t tmy,
        const reskia_sampling_options_t *sampling,
        const reskia_matrix_t *localMatrix) {
    if (image == nullptr || sampling == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(
            static_cast<SkTileMode>(tmx),
            static_cast<SkTileMode>(tmy),
            *reinterpret_cast<const SkSamplingOptions *>(sampling),
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}
```

If `static_*_make` does not normalize NULL `sk_sp` to `0`, normalize it explicitly in the C API.

### Borrowed Return API

```cpp
reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface) {
    if (surface == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkSurface *>(surface)->getCanvas());
}
```

The returned pointer is surface-owned and must not be deleted by the caller.

## Smoke Tests

For hardened APIs, test the cases that match the risk.

- NULL receiver.
- Required pointer NULL.
- Invalid handle.
- Stale handle.
- Optional pointer NULL is allowed.
- `count > 0` with array NULL.
- Invalid rowBytes / storage.
- Factory failure returns `0`.
- Minimal valid path.
- Returned handle can be deleted or released.
- Borrowed pointer is not deleted by the caller.
- Callback NULL no-op.
- Callback works with NULL context.

Not every API needs every case. Choose the cases that match the API contract.

For `void` APIs, no-crash behavior is the smoke check. For APIs with return values, explicitly check the invalid-input return value.

Tests often have early returns, so release every added handle or pointer on every exit path.

## Edit Workflow

1. Check the upstream Skia public header and implementation.
2. Check the existing C API shape and ABI compatibility.
3. Add guards for receivers, required pointers, handles, buffers, and callbacks.
4. Align return values with invalid-input rules.
5. Document ownership and lifetime in the header.
6. Add smoke tests for the relevant risks.
7. Update coverage, checklists, or work records.

Keep changes scoped to the target APIs. Do not mix unrelated refactors or broad formatting.

## Verification

Basic checks:

```bash
git diff --check
cmake -S skia -B skia/cmake-build-capi-safety -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-capi-safety -j 8
```

When adding tests:

```bash
cmake -S skia -B skia/cmake-build-capi-safety-tests \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-capi-safety-tests -j 8
ctest --test-dir skia/cmake-build-capi-safety-tests --output-on-failure
```

For coverage-related changes, rerun the generator when needed.

```bash
python3 scripts/generate_public_api_coverage.py \
  --output docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv
```

## Related Documents

- `docs/en/README.md`
- `docs/en/guides/repository-structure.md`
- `docs/ja/plans/c-binding-remediation/README.md`
- `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
- `docs/ja/plans/stability-hardening/00-plan.md`
