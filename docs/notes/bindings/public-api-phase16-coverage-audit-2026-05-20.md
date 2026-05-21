# Public API Coverage Phase 16 Audit

Date: 2026-05-20

Superseded note: this audit records the Phase 16 state. Phase 26 later freezes
the post-coverage-expansion state with `missing 0` and `deferred 5`; see
`docs/notes/bindings/public-api-phase26-coverage-freeze-audit-2026-05-21.md`.

## Snapshot

Latest `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`:

| status | count |
| --- | ---: |
| `covered` | 2604 |
| `missing` | 252 |
| `false_positive` | 274 |
| `na` | 154 |
| `no_public_methods_found` | 104 |
| `split_covered` | 33 |
| `partial` | 0 |
| `overcovered` | 0 |
| `deferred` | 0 |

The Phase 16 exit invariant for generated status quality is satisfied:
`partial`, `overcovered`, and `deferred` are all zero.

## Current Missing Routing

The old Phase 7 routing index is now stale after Phases 11-15. Do not use it as
the canonical next-work source without resynchronizing it against the current
matrix. The Phase 16 current routing is captured in:

- `docs/plans/c-binding-remediation/checklists/public-api-phase-16-current-missing-routing.csv`

Current `missing` distribution:

| area | missing | next route |
| --- | ---: | --- |
| `include/gpu` | 151 | Phase 17 GPU small-gap and provider split |
| `modules/svg` | 74 | Phase 18 SVG resource and value polish |
| `modules/sksg` | 25 | Phase 19 SkSG graph polish |
| `include/codec` | 1 | Phase 20 global registration design |
| `include/core` | 1 | Phase 20 global registration design |

## Status Vocabulary

Use these matrix statuses consistently:

- `covered`: exact C ABI symbol matched the public method/factory.
- `split_covered`: method is covered by multiple typed or renamed C ABI entry points.
- `missing`: visible implementation or design follow-up.
- `na`: deliberately outside Reskia's C ABI surface, usually platform/internal/debug.
- `false_positive`: generator saw a C++ convenience/operator/destructor/internal hook that should not map to a direct C ABI method.
- `no_public_methods_found`: public class/struct row has no extracted public methods.
- `partial`: temporary generator warning for loose symbol matches; should remain zero.
- `overcovered`: temporary audit status for false exact matches; should remain zero.
- `deferred`: at Phase 16 this was a temporary backlog status and was expected to remain zero. Phase 26 reuses it for a reviewed, named follow-up bridge backlog; use the Phase 26 audit for the current meaning.

## Smoke Coverage Map

Representative smoke tests that anchor Phases 11-15:

| area | tests |
| --- | --- |
| GPU / Graphite | `c_skia_gpu_context_capi_smoke`, `c_skia_gpu_surface_capi_smoke` |
| SVG | `c_skia_svg_dom_capi_smoke`, `c_skia_svg_types_capi_smoke`, `c_skia_svg_canvas_capi_smoke`, `c_skia_open_type_svg_decoder_invalid_input_smoke` |
| SkSG | `c_skia_sksg_capi_smoke`, `c_skia_sksg_smoke` |
| Text stack | `c_skia_shaper_capi_smoke`, `c_skia_unicode_capi_smoke`, `c_skia_paragraph_text_style_capi_smoke`, `c_skia_paragraph_builder_capi_smoke`, `c_skia_paragraph_font_collection_capi_smoke`, `c_skia_paragraph_style_capi_smoke`, `c_skia_paragraph_typeface_font_provider_capi_smoke` |
| Skottie / resources / callbacks | `c_skia_skottie_smoke`, `c_skia_skresources_capi_smoke`, `c_skia_codec_invalid_input_smoke` |

## Next Work Order

1. Phase 17: split GPU into low-risk value wrappers first. YUV(A) backend texture
   info, mock/backend drawable values, backend semaphore/options wrappers, and
   Graphite compatibility queries should precede async/provider callbacks.
2. Phase 18: handle SVG value accessors and node factories, then design the
   SVG resource loading owner model for `SkSVGImage::LoadImage`.
3. Phase 19: finish SkSG graph/effect factory helpers and decide whether
   invalidation rectangle iteration should be exposed.
4. Phase 20: design process-global registration for `SkCodec::Register` and
   `SkTypeface::Register`; do not bind these as ordinary borrowed callbacks.

## Phase 16 Result

Phase 16 did not add runtime C ABI. It refreshed the residual view, documented
the status vocabulary, mapped smoke coverage, and created a current missing
routing file so future phases do not rely on the stale Phase 7 index.
