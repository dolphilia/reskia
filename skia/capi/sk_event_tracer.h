#ifndef RAIA_SKIA_SK_EVENT_TRACER_H
#define RAIA_SKIA_SK_EVENT_TRACER_H

#include <stdint.h>

#include "reskia_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_event_tracer_t reskia_event_tracer_t;
typedef uint64_t reskia_event_tracer_handle_t;

typedef const uint8_t *(*reskia_event_tracer_get_category_group_enabled_proc_t)(
        const char *name,
        void *user_data);
typedef const char *(*reskia_event_tracer_get_category_group_name_proc_t)(
        const uint8_t *category_enabled_flag,
        void *user_data);
typedef reskia_event_tracer_handle_t (*reskia_event_tracer_add_trace_event_proc_t)(
        char phase,
        const uint8_t *category_enabled_flag,
        const char *name,
        uint64_t id,
        int32_t num_args,
        const char **arg_names,
        const uint8_t *arg_types,
        const uint64_t *arg_values,
        uint8_t flags,
        void *user_data);
typedef void (*reskia_event_tracer_update_trace_event_duration_proc_t)(
        const uint8_t *category_enabled_flag,
        const char *name,
        reskia_event_tracer_handle_t handle,
        void *user_data);
typedef void (*reskia_event_tracer_new_tracing_section_proc_t)(
        const char *name,
        void *user_data);

reskia_event_tracer_t *SkEventTracer_new(
        reskia_event_tracer_get_category_group_enabled_proc_t get_category_group_enabled,
        reskia_event_tracer_get_category_group_name_proc_t get_category_group_name,
        reskia_event_tracer_add_trace_event_proc_t add_trace_event,
        reskia_event_tracer_update_trace_event_duration_proc_t update_trace_event_duration,
        reskia_event_tracer_new_tracing_section_proc_t new_tracing_section,
        void *user_data,
        reskia_callback_release_proc_t release_proc);
void SkEventTracer_delete(reskia_event_tracer_t *tracer);
bool SkEventTracer_SetInstance(reskia_event_tracer_t *tracer, bool leak_tracer); // tracer is consumed. Skia destroys it even on failure.
reskia_event_tracer_t *SkEventTracer_GetInstance(void); // Borrowed singleton; do not delete.
const uint8_t *SkEventTracer_getCategoryGroupEnabled(reskia_event_tracer_t *tracer, const char *name);
const char *SkEventTracer_getCategoryGroupName(reskia_event_tracer_t *tracer, const uint8_t *category_enabled_flag);
reskia_event_tracer_handle_t SkEventTracer_addTraceEvent(
        reskia_event_tracer_t *tracer,
        char phase,
        const uint8_t *category_enabled_flag,
        const char *name,
        uint64_t id,
        int32_t num_args,
        const char **arg_names,
        const uint8_t *arg_types,
        const uint64_t *arg_values,
        uint8_t flags);
void SkEventTracer_updateTraceEventDuration(
        reskia_event_tracer_t *tracer,
        const uint8_t *category_enabled_flag,
        const char *name,
        reskia_event_tracer_handle_t handle);
void SkEventTracer_newTracingSection(reskia_event_tracer_t *tracer, const char *name);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_EVENT_TRACER_H
