# Skottie PropertyObserver Lazy Handle C ABI Design

Date: 2026-05-17

## Scope

This memo covers the Phase 14 binding shape for `skottie::PropertyObserver`
property callbacks:

- `onColorProperty`
- `onOpacityProperty`
- `onTextProperty`
- `onTransformProperty`

The node traversal callbacks (`onEnterNode` / `onLeavingNode`) were already
implemented earlier in Phase 14.

## Upstream Ownership Model

Skia passes each property as:

```cpp
const PropertyObserver::LazyHandle<PropertyHandleT>&
```

where `LazyHandle<T>` is a `std::function<std::unique_ptr<T>()>`. The callback
can choose whether to materialize the handle. Once materialized, the
`PropertyHandle` owns references to the internal scene graph node and optional
revalidator, so the handle can be used after the observer callback returns.

## C ABI Model

The C ABI mirrors the upstream split:

- `reskia_skottie_*_property_lazy_handle_t` is borrowed and callback-scoped.
- `Skottie_*PropertyLazyHandle_materialize` returns an owned
  `reskia_skottie_*_property_handle_t`.
- Owned property handles are released with `Skottie_*PropertyHandle_delete`.

The lazy handle pointer must not be retained by C callers. If a caller needs to
read or mutate a property after the callback, it must materialize and store the
owned property handle instead.

## Callback Registration

`Skottie_PropertyObserver_new` remains as the node-only constructor for
backward-compatible source use.

`Skottie_PropertyObserver_newWithProperties` registers both node callbacks and
property callbacks. The object remains `SkRefCnt`-managed, and builder setters
retain borrowed observer pointers with `sk_ref_sp`.

## Value Access

Color and opacity expose scalar get/set helpers. Text exposes get/set through
the existing `TextPropertyValue` wrapper. Transform exposes a C value struct
with anchor, position, scale, rotation, skew, and skew-axis fields.

All `set` helpers call through the upstream `PropertyHandle::set`, preserving
Skia's revalidation behavior.

## Follow-Up Boundary

Skottie text shaper rows are separate from property observation. They are handled
by a separate Phase 14 shaper result wrapper so this callback batch stays focused
on observer ownership and lazy property materialization.
