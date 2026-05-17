# Skottie Shaper Result C ABI Design

Date: 2026-05-17

## Scope

This memo covers the Phase 14 binding shape for:

- `skottie::Shaper::Shape(text, desc, point, fontMgr)`
- `skottie::Shaper::Shape(text, desc, box, fontMgr)`

## C ABI Shape

`Skottie_Shaper_Shape` is the exact public helper used by the coverage generator.
It accepts either a point or a box:

- `use_box == false`: shape at `(x, y)` and ignore `box`.
- `use_box == true`: shape inside `box`; null `box` returns null.

`Skottie_Shaper_ShapeAtPoint` and `Skottie_Shaper_ShapeInBox` are convenience
aliases over the exact helper.

The returned `reskia_skottie_shaper_result_t` owns a `skottie::Shaper::Result`
and is released with `Skottie_Shaper_Result_delete`.

## Descriptor Mapping

The C ABI reuses `TextPropertyValue` as the shaping descriptor source. The
wrapper copies the fields that correspond to `Shaper::TextDesc`: typeface,
text-size bounds, line metrics, alignments, resize/linebreak policy, direction,
capitalization, max lines, and locale.

The text string is passed separately, matching the upstream `Shape` API.

## Exposed Result Surface

The first C ABI batch exposes metadata that is stable and cheap to query:

- fragment count
- missing glyph count
- final shaping scale
- computed visual bounds

The detailed fragment/glyph-run iteration surface is intentionally left for a
later coverage polish batch because it requires a larger set of array and
borrowed-slice conventions for `SkGlyphID`, positions, clusters, and run fonts.
