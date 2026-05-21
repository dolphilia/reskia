# Public API Coverage Phase 26 Freeze Audit

Date: 2026-05-21

Superseded note: this audit froze the Phase 26 state with `missing 0` and
`deferred 5`. Phase 28 later implemented the Ganesh external texture bridge and
returned `deferred` to 0. Phase 29 is the final coverage freeze with
`missing 0` / `deferred 0`; see
`docs/notes/bindings/public-api-phase29-final-coverage-freeze-2026-05-21.md`.

## Snapshot

Source: `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`

| status | count |
| --- | ---: |
| `covered` | 2806 |
| `missing` | 0 |
| `false_positive` | 275 |
| `na` | 198 |
| `no_public_methods_found` | 104 |
| `split_covered` | 33 |
| `partial` | 0 |
| `overcovered` | 0 |
| `deferred` | 5 |

Phase 26 freeze invariant:

- `missing` is zero.
- `partial` and `overcovered` are zero.
- `deferred` is intentionally non-zero and contains only Ganesh external texture bridge rows.

## Deferred Rows

The only `deferred` rows are:

| header | class | method | reason |
| --- | --- | --- | --- |
| `include/gpu/ganesh/GrExternalTextureGenerator.h` | `GrExternalTexture` | `getBackendTexture` | Needs a concrete external texture bridge tied to backend texture copy/ownership. |
| `include/gpu/ganesh/GrExternalTextureGenerator.h` | `GrExternalTexture` | `dispose` | Needs exactly-once dispose callback semantics. |
| `include/gpu/ganesh/GrExternalTextureGenerator.h` | `GrExternalTextureGenerator` | constructor | Only useful as part of a derived generator bridge. |
| `include/gpu/ganesh/GrExternalTextureGenerator.h` | `GrExternalTextureGenerator` | `onGenerateTexture` | Internal generator plumbing; C ABI should expose higher-level callback factory. |
| `include/gpu/ganesh/GrExternalTextureGenerator.h` | `GrExternalTextureGenerator` | `generateExternalTexture` | Needs a callback bridge returning an external texture object. |

These rows are real public API gaps, not `na`. They are deferred because the safe C ABI must be designed around `SkImages::DeferredFromTextureGenerator`, `GrBackendTexture` copying, and `dispose` lifetime.

## Status Vocabulary After Freeze

- `covered`: exact or reviewed C ABI surface exists.
- `split_covered`: public method is covered by multiple typed or renamed C ABI entry points.
- `missing`: ordinary unhandled public API gap. This must stay zero after Phase 26.
- `deferred`: reviewed, intentionally postponed implementation candidate with a named follow-up bridge. After Phase 26 this is allowed only for the five Ganesh external texture rows.
- `na`: deliberately outside Reskia's portable C ABI surface, usually platform-only, internal, debug, or unavailable optional backend.
- `false_positive`: generator saw a C++ convenience/operator/destructor/internal hook that should not map to a direct C ABI method.
- `no_public_methods_found`: public class/struct row has no extracted public methods.
- `partial`: temporary generator warning for loose symbol matches. This must stay zero.
- `overcovered`: temporary audit status for false exact matches. This must stay zero.

## Verification State

Recently verified:

- `python3 scripts/generate_public_api_coverage.py`
- `python3 -m py_compile scripts/generate_public_api_coverage.py`
- source SVG build and smoke for `test_svg_image_capi_smoke`
- source SVG smoke for `test_svg_types_capi_smoke`

Historical verification debt:

- At Phase 26 time, `cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke -j 8` reached the link step but failed on the pre-existing `libsvg.a` unresolved symbol `SkShaper::Make(sk_sp<SkFontMgr>)`.
- Phase 27 fixed this by adding Apple prebuilt fallback `skunicode` / `skshaper` targets. The Phase 26 item is historical context, not active coverage debt.

## Next Work

Recommended next phases:

1. Phase 27: Build Verification Debt
   - isolate the `libsvg.a` / `SkShaper::Make(sk_sp<SkFontMgr>)` link issue,
   - document which build configurations can verify GPU C API changes,
   - fix the link wiring if the scope remains small.

2. Phase 28: Ganesh External Texture Dedicated Bridge
   - design and implement a safe C callback bridge around `SkImages::DeferredFromTextureGenerator`,
   - expose a concrete external texture object with backend texture and dispose callbacks,
   - move the five `deferred` rows to `covered` when verified.
