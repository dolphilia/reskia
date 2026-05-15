#include <cstdio>

#include "capi/sk_canvas.h"
#include "capi/sk_event_tracer.h"
#include "capi/sk_i_size.h"
#include "capi/sk_paint.h"
#include "capi/sk_paint_filter_canvas.h"
#include "capi/sk_rect.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_rect.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[event-paint-filter-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

struct EventState {
    uint8_t enabled = 1;
    int category_enabled_calls = 0;
    int category_name_calls = 0;
    int add_calls = 0;
    int update_calls = 0;
    int section_calls = 0;
};

const uint8_t *event_get_category_group_enabled(const char *, void *user_data) {
    auto *state = static_cast<EventState *>(user_data);
    state->category_enabled_calls += 1;
    return &state->enabled;
}

const char *event_get_category_group_name(const uint8_t *, void *user_data) {
    auto *state = static_cast<EventState *>(user_data);
    state->category_name_calls += 1;
    return "reskia-test";
}

reskia_event_tracer_handle_t event_add_trace_event(
        char,
        const uint8_t *,
        const char *,
        uint64_t,
        int32_t,
        const char **,
        const uint8_t *,
        const uint64_t *,
        uint8_t,
        void *user_data) {
    auto *state = static_cast<EventState *>(user_data);
    state->add_calls += 1;
    return 42;
}

void event_update_trace_event_duration(const uint8_t *, const char *, reskia_event_tracer_handle_t, void *user_data) {
    auto *state = static_cast<EventState *>(user_data);
    state->update_calls += 1;
}

void event_new_tracing_section(const char *, void *user_data) {
    auto *state = static_cast<EventState *>(user_data);
    state->section_calls += 1;
}

struct PaintFilterState {
    int calls = 0;
    bool reject = false;
    int released = 0;
};

bool paint_filter(reskia_paint_t *, void *user_data) {
    auto *state = static_cast<PaintFilterState *>(user_data);
    state->calls += 1;
    return !state->reject;
}

void paint_filter_release(void *user_data) {
    auto *state = static_cast<PaintFilterState *>(user_data);
    state->released += 1;
}

bool smoke_event_tracer() {
    EventState state;
    reskia_event_tracer_t *tracer = SkEventTracer_new(
            event_get_category_group_enabled,
            event_get_category_group_name,
            event_add_trace_event,
            event_update_trace_event_duration,
            event_new_tracing_section,
            &state,
            nullptr);
    if (!check(tracer != nullptr, "SkEventTracer_new")) {
        return false;
    }
    const uint8_t *enabled = SkEventTracer_getCategoryGroupEnabled(tracer, "reskia");
    if (!check(enabled != nullptr && *enabled == 1 && state.category_enabled_calls == 1,
               "SkEventTracer_getCategoryGroupEnabled")) {
        SkEventTracer_delete(tracer);
        return false;
    }
    if (!check(SkEventTracer_getCategoryGroupName(tracer, enabled) != nullptr &&
               state.category_name_calls == 1,
               "SkEventTracer_getCategoryGroupName")) {
        SkEventTracer_delete(tracer);
        return false;
    }
    reskia_event_tracer_handle_t handle = SkEventTracer_addTraceEvent(
            tracer, 'B', enabled, "event", 1, 0, nullptr, nullptr, nullptr, 0);
    if (!check(handle == 42 && state.add_calls == 1, "SkEventTracer_addTraceEvent")) {
        SkEventTracer_delete(tracer);
        return false;
    }
    SkEventTracer_updateTraceEventDuration(tracer, enabled, "event", handle);
    SkEventTracer_newTracingSection(tracer, "section");
    if (!check(state.update_calls == 1 && state.section_calls == 1,
               "SkEventTracer update/section")) {
        SkEventTracer_delete(tracer);
        return false;
    }

    bool installed = SkEventTracer_SetInstance(tracer, true);
    if (!check(installed, "SkEventTracer_SetInstance")) {
        return false;
    }
    reskia_event_tracer_t *global = SkEventTracer_GetInstance();
    if (!check(global != nullptr, "SkEventTracer_GetInstance")) {
        return false;
    }
    (void)SkEventTracer_getCategoryGroupEnabled(global, "global");
    return true;
}

bool smoke_paint_filter_canvas() {
    PaintFilterState state;
    reskia_canvas_t *target = SkCanvas_newWithSizeProps(16, 16, nullptr);
    reskia_paint_filter_canvas_t *filter = SkPaintFilterCanvas_new(
            target,
            paint_filter,
            &state,
            paint_filter_release);
    reskia_paint_t *paint = SkPaint_new();
    sk_rect_t rect_handle = SkRect_MakeLTRB(1.0f, 1.0f, 8.0f, 8.0f);
    auto *rect = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(rect_handle));
    if (!check(target != nullptr && filter != nullptr && paint != nullptr && rect != nullptr,
               "SkPaintFilterCanvas setup")) {
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkPaintFilterCanvas_delete(filter);
        return false;
    }

    reskia_canvas_t *as_canvas = SkPaintFilterCanvas_asCanvas(filter);
    if (!check(as_canvas != nullptr, "SkPaintFilterCanvas_asCanvas")) {
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkPaintFilterCanvas_delete(filter);
        return false;
    }
    SkCanvas_drawRect(as_canvas, rect_handle, paint);
    if (!check(state.calls > 0, "SkPaintFilterCanvas filter callback")) {
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkPaintFilterCanvas_delete(filter);
        return false;
    }
    sk_i_size_t size = SkPaintFilterCanvas_getBaseLayerSize(filter);
    if (!check(size != 0,
               "SkPaintFilterCanvas_getBaseLayerSize")) {
        static_sk_i_size_delete(size);
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkPaintFilterCanvas_delete(filter);
        return false;
    }
    auto *recording_context = SkPaintFilterCanvas_recordingContext(filter);
    if (!check(recording_context == nullptr,
               "SkPaintFilterCanvas_recordingContext raster null")) {
        static_sk_i_size_delete(size);
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkPaintFilterCanvas_delete(filter);
        return false;
    }

    static_sk_i_size_delete(size);
    static_sk_rect_delete(rect_handle);
    SkPaint_delete(paint);
    SkPaintFilterCanvas_delete(filter);
    // The wrapped canvas is borrowed by the filter canvas. This smoke leaves
    // the small target canvas to process teardown after exercising that path.
    return check(state.released == 1, "SkPaintFilterCanvas release proc");
}

}  // namespace

int main() {
    if (!smoke_event_tracer()) {
        return 1;
    }
    if (!smoke_paint_filter_canvas()) {
        return 1;
    }
    std::fprintf(stdout, "[event-paint-filter-utils-smoke] PASS\n");
    return 0;
}
