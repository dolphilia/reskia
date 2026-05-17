# Phase 14 Registration / Provider Routing

Date: 2026-05-17

## Scope

This note closes the Phase 14 routing decision for callback/provider/registration
rows that were not implemented in the SkPngChunkReader, skresources, skottie,
and shaper batches.

## Keep As Explicit Follow-Up

### `SkCodec::Register`

`SkCodec::Register` installs a process-global codec factory. Upstream exposes no
unregister API, so a C ABI wrapper needs a policy for:

- callback lifetime after registration
- disabling callbacks after user data destruction
- repeated registrations and replacement behavior
- transfer of `std::unique_ptr<SkStream>` into C-owned or C-observed stream data
- transfer of the returned `std::unique_ptr<SkCodec>` back into Skia

Do not implement this as a simple borrowed callback. It should be a dedicated
global-registration batch with process-lifetime owner records and a disabled
callback fallback.

### `SkTypeface::Register`

`SkTypeface::Register` has the same process-global issue and additionally
requires `SkFontArguments` mapping and `SkStreamAsset` transfer. It should share
the same global-registration policy as `SkCodec::Register`.

## SVG Resource Loading

`SkSVGImage::LoadImage` is not a callback registration API, but it sits on top
of `skresources::ResourceProvider` and SVG-specific values:

- `SkSVGIRI`
- `SkSVGPreserveAspectRatio`
- `SkSVGImage::ImageInfo`

The skresources provider foundation is now available, but the SVG value/result
wrappers should be designed together with remaining SVG node/resource work. Route
this to a later SVG resource polish batch instead of Phase 15 platform/internal
NA sweep.

## GPU / Graphite Provider And Async Rows

Graphite async readback, `ImageProvider`, `Recorder::snap`,
`Context::insertRecording`, deferred canvas transfer, and platform allocator
interfaces require GPU-specific owner handles and platform backend lifetime
rules. They should not be mixed with core/global registration:

- route Graphite async callbacks to a GPU async/provider phase
- route allocator interfaces to platform backend phases
- keep recording/canvas transfer rows as real gaps until the Graphite ownership
  model is explicit

## Phase 15 Boundary

Phase 15 should classify platform/internal/debug rows that are clearly not
ordinary C ABI surface:

- Android framework-only APIs
- deprecated Android-framework-only `Sk3DView` camera helpers
- abstract base callback/destructor hooks
- debug trace sinks
- low-priority internal geometry helper modules

Global registration and GPU provider rows remain visible follow-ups rather than
being hidden as `na`.
