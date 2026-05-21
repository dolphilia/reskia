# Phase 20 Global Registration C API Design

- Date: 2026-05-21
- Work start: 2026-05-21 11:14:18 JST
- Scope: `SkCodec::Register` and `SkTypeface::Register`

## Policy

These APIs install process-global callbacks and upstream does not provide a full
unregister API. Reskia exposes them as initialization-time registration APIs,
with context replacement but without a `clear` API.

Common rules:

- callback function pointers must remain valid for process lifetime;
- `user_data` is retained by Reskia after a successful registration;
- `release_proc` is called once when the registration context is replaced;
- `NULL` callbacks reject the registration and do not replace the current
  context;
- callbacks take transferred stream handles and must consume or delete those
  handles before returning.

## `SkCodec_Register`

The current upstream also exposes `SkCodecs::Register(Decoder)` for decoder
replacement by string id. Reskia uses a single fixed decoder id, `reskia`, and
maps the class-level `SkCodec::Register` coverage row onto that decoder slot.

The C API separates the two upstream callbacks:

- `reskia_codec_peek_proc_t`: borrowed byte span, valid only during callback;
- `reskia_codec_make_proc_t`: transferred `sk_stream_t`, optional result output,
  and returned transferred `sk_codec_t`.

Replacement is supported by reinstalling the `reskia` decoder id. The old
context is released after the new context is published. Callback execution holds
a shared context snapshot, so replacement does not invalidate an in-flight call.

## `SkTypeface_Register`

Upstream associates each registered factory function with a `FactoryId`, but the
factory function itself receives only `SkStreamAsset` and `SkFontArguments`.
There is no callback parameter that identifies the matched factory id.

To avoid dispatching a dynamic set of C callbacks without knowing the matched
id, Reskia fixes the first successful factory id for the process:

- the first `SkTypeface_Register(id, ...)` installs the upstream trampoline for
  that id;
- later calls with the same id replace the retained context;
- calls with another id return `false` and do not replace the current context.

The C callback receives a transferred `sk_stream_asset_t` and a borrowed
`SkFontArguments` view valid only during the callback. The callback returns a
transferred `sk_typeface_t`; `0` maps to a null `sk_sp<SkTypeface>`.

## Verification

`c_skia_codec_smoke` verifies:

- codec registration rejects null callbacks;
- codec peek/make callbacks are dispatched for the fixed `reskia` decoder id;
- codec context replacement releases the previous context once;
- typeface registration rejects null callback, zero id, and different-id
  replacement;
- typeface same-id replacement releases the previous context once;
- test-owned stack contexts are replaced by no-release contexts before process
  teardown.
