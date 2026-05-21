# Public API Coverage Phase 28 Ganesh External Texture Bridge

Date: 2026-05-21

## Scope

Phase 28 closes the five deliberate `deferred` rows from Phase 26:

- `GrExternalTexture::getBackendTexture`
- `GrExternalTexture::dispose`
- `GrExternalTextureGenerator::GrExternalTextureGenerator`
- `GrExternalTextureGenerator::onGenerateTexture`
- `GrExternalTextureGenerator::generateExternalTexture`

## C ABI Shape

The bridge introduces a concrete C-owned external texture object:

- `GrExternalTexture_new`
- `GrExternalTexture_delete`
- `GrExternalTexture_getBackendTexture`
- `GrExternalTexture_dispose`

`GrExternalTexture_new` copies the supplied `GrBackendTexture`. `dispose` is idempotent. `delete` also disposes once, then invokes the release callback once.

The bridge also introduces a concrete callback generator:

- `GrExternalTextureGenerator_new`
- `GrExternalTextureGenerator_delete`
- `GrExternalTextureGenerator_generateExternalTexture`
- `SkImages_DeferredFromTextureGenerator`

`GrExternalTextureGenerator_new` stores a C callback and user data. Each generation callback returns an owned `reskia_gr_external_texture_t*`; the bridge consumes that object as a `std::unique_ptr<GrExternalTexture>`.

## Ownership

- External texture objects are caller-owned until passed back from the generator callback.
- A generator callback return value is consumed by the bridge; callers must not delete it after returning.
- `SkImages_DeferredFromTextureGenerator` consumes the generator. Callers must not delete the generator after passing it to this function.
- `GrExternalTexture_getBackendTexture` returns an owned backend texture copy.
- `dispose_proc` receives a borrowed pointer to the stored backend texture.
- `dispose_proc` is called at most once per external texture object.
- `release_proc` is called once when the external texture object or generator object is destroyed.

## Verification

The GPU context smoke now covers:

- null input paths,
- direct external texture backend texture copy,
- idempotent dispose and release,
- generator callback dispatch,
- `SkImages_DeferredFromTextureGenerator` ownership transfer.

Command:

```sh
cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke -j 8
skia/cmake-build-codex-phase9-gpu/test_gpu_context_capi_smoke
```

Result:

- build/link succeeded,
- runtime reported `SKIP: Metal device is unavailable in this environment`,
- smoke returned `PASS`.
