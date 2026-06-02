# C API / Handle Binding Overview

This document explains Reskia's C API bindings and handle bindings. For per-API safety rules, see `docs/en/guides/c-api-safety-guidelines.md`.

## Policy

Reskia exposes Skia public classes, public methods, static factories, and helpers through a C ABI where practical.

Before exposing an API, check:

- Whether it exists in upstream Skia public headers.
- Whether its types can be represented safely in a C ABI.
- Whether the pointer API or handle API is the better surface.
- Whether ownership and lifetime can be explained.
- Whether it depends on optional modules or platform features.
- Whether the coverage matrix can record its status.

## Two API Layers

### `skia/capi`

`skia/capi` is the pointer-oriented API.

Properties:

- Exposes `extern "C"` functions.
- Uses opaque pointer types for Skia objects.
- Stays close to the Skia C++ API shape.
- Documents ownership, NULL input behavior, borrowed lifetimes, and callback lifetimes in headers.

Example:

```c
reskia_image_t *SkImage_newRaster(...);
void SkImage_delete(reskia_image_t *image);
bool SkImage_readPixels(...);
```

### `skia/handles`

`skia/handles` is the integer-handle API.

Properties:

- Exposes integer handles such as `sk_image_t`.
- Stores objects in an internal handle table.
- Detects invalid and stale handles.
- Helps language bindings avoid raw pointers.

Example:

```c
sk_image_t static_sk_image_make(...);
void static_sk_image_delete(sk_image_t image);
```

## Choosing a Layer

| Aspect | `skia/capi` | `skia/handles` |
| --- | --- | --- |
| Boundary | Close to raw pointers | Integer handles |
| Expressiveness | Close to Skia C++ APIs | Easier for bindings |
| Lifetime | Managed by caller plus comments | Managed by handle table |
| Main use | Thin C / FFI wrappers | Bindings that should avoid raw pointers |

When the same concept exists in both layers, align ownership and failure values.

## Naming

API names should preserve the Skia type and the meaning of the method or factory.

Prefer:

- Use meaningful overload names instead of numbered suffixes.
- Return `0` / `NULL` for factory failure where appropriate.
- Follow existing `static_sk_*` naming for handle APIs.

Avoid:

- Temporary names such as `_2` or `_3`.
- Mixing `get` and `new` when ownership is unclear.
- Keeping APIs that correspond to removed upstream Skia APIs.

## Ownership

Return values should fall into one of these categories.

| Category | Meaning |
| --- | --- |
| `caller-owned` | Caller must delete or release the value. |
| `borrowed` | Caller must not release it; lifetime depends on a parent object or storage. |
| `retained` | Refcount was increased and the result is caller-owned. |
| `consumed` | Callee takes ownership of an argument. |
| `callback-only` | Valid only during callback execution. |

Headers should document required / optional inputs, return ownership, and failure values.

## Coverage Matrix

Public API coverage is tracked in `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`.

Main statuses:

- `covered`: covered by a C API.
- `split_covered`: covered by multiple C APIs.
- `false_positive`: detected by the generator but not a real target.
- `na`: intentionally not exposed through C ABI.
- `missing`: needs work.

See `docs/en/guides/public-api-coverage-workflow.md` for generation and review workflow.

## CMake Integration

C API and handle sources are compiled into the `reskia` target.

Relevant areas:

- `skia/capi/*.h`, `skia/capi/*.cpp`
- `skia/handles/*.h`, `skia/handles/*.cpp`
- `cmake/reskia/sources-*.cmake`
- `skia/CMakeLists.txt`

When adding a new source file, update the CMake source list and verify the build.

## Add / Change Workflow

1. Check the upstream Skia public header.
2. Decide whether the API should be exposed and what constraints apply.
3. Choose the API name, arguments, return ownership, and failure value.
4. Implement it under `skia/capi` or `skia/handles`.
5. Add safety comments and smoke tests.
6. Update the coverage matrix and stale C API report.
7. Run configure / build / tests.

Follow `docs/en/guides/c-api-safety-guidelines.md` for safety details.
