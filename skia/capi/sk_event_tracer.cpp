#include "sk_event_tracer.h"

#include "include/utils/SkEventTracer.h"

namespace {

class ReskiaEventTracer final : public SkEventTracer {
public:
    ReskiaEventTracer(
            reskia_event_tracer_get_category_group_enabled_proc_t get_category_group_enabled,
            reskia_event_tracer_get_category_group_name_proc_t get_category_group_name,
            reskia_event_tracer_add_trace_event_proc_t add_trace_event,
            reskia_event_tracer_update_trace_event_duration_proc_t update_trace_event_duration,
            reskia_event_tracer_new_tracing_section_proc_t new_tracing_section,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : get_category_group_enabled_(get_category_group_enabled)
        , get_category_group_name_(get_category_group_name)
        , add_trace_event_(add_trace_event)
        , update_trace_event_duration_(update_trace_event_duration)
        , new_tracing_section_(new_tracing_section)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaEventTracer() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    const uint8_t *getCategoryGroupEnabled(const char *name) override {
        static const uint8_t disabled = 0;
        if (get_category_group_enabled_ == nullptr) {
            return &disabled;
        }
        const uint8_t *enabled = get_category_group_enabled_(name, user_data_);
        return enabled != nullptr ? enabled : &disabled;
    }

    const char *getCategoryGroupName(const uint8_t *category_enabled_flag) override {
        static const char stub[] = "stub";
        if (get_category_group_name_ == nullptr) {
            return stub;
        }
        const char *name = get_category_group_name_(category_enabled_flag, user_data_);
        return name != nullptr ? name : stub;
    }

    SkEventTracer::Handle addTraceEvent(
            char phase,
            const uint8_t *category_enabled_flag,
            const char *name,
            uint64_t id,
            int32_t num_args,
            const char **arg_names,
            const uint8_t *arg_types,
            const uint64_t *arg_values,
            uint8_t flags) override {
        if (add_trace_event_ == nullptr) {
            return 0;
        }
        return add_trace_event_(
                phase,
                category_enabled_flag,
                name,
                id,
                num_args,
                arg_names,
                arg_types,
                arg_values,
                flags,
                user_data_);
    }

    void updateTraceEventDuration(
            const uint8_t *category_enabled_flag,
            const char *name,
            SkEventTracer::Handle handle) override {
        if (update_trace_event_duration_ == nullptr) {
            return;
        }
        update_trace_event_duration_(category_enabled_flag, name, handle, user_data_);
    }

    void newTracingSection(const char *name) override {
        if (new_tracing_section_ == nullptr) {
            return;
        }
        new_tracing_section_(name, user_data_);
    }

private:
    reskia_event_tracer_get_category_group_enabled_proc_t get_category_group_enabled_;
    reskia_event_tracer_get_category_group_name_proc_t get_category_group_name_;
    reskia_event_tracer_add_trace_event_proc_t add_trace_event_;
    reskia_event_tracer_update_trace_event_duration_proc_t update_trace_event_duration_;
    reskia_event_tracer_new_tracing_section_proc_t new_tracing_section_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

} // namespace

extern "C" {

reskia_event_tracer_t *SkEventTracer_new(
        reskia_event_tracer_get_category_group_enabled_proc_t get_category_group_enabled,
        reskia_event_tracer_get_category_group_name_proc_t get_category_group_name,
        reskia_event_tracer_add_trace_event_proc_t add_trace_event,
        reskia_event_tracer_update_trace_event_duration_proc_t update_trace_event_duration,
        reskia_event_tracer_new_tracing_section_proc_t new_tracing_section,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_event_tracer_t *>(new ReskiaEventTracer(
            get_category_group_enabled,
            get_category_group_name,
            add_trace_event,
            update_trace_event_duration,
            new_tracing_section,
            user_data,
            release_proc));
}

void SkEventTracer_delete(reskia_event_tracer_t *tracer) {
    delete reinterpret_cast<SkEventTracer *>(tracer);
}

bool SkEventTracer_SetInstance(reskia_event_tracer_t *tracer, bool leak_tracer) {
    if (tracer == nullptr) {
        return false;
    }
    (void) leak_tracer;
    return SkEventTracer::SetInstance(reinterpret_cast<SkEventTracer *>(tracer));
}

reskia_event_tracer_t *SkEventTracer_GetInstance(void) {
    return reinterpret_cast<reskia_event_tracer_t *>(SkEventTracer::GetInstance());
}

const uint8_t *SkEventTracer_getCategoryGroupEnabled(reskia_event_tracer_t *tracer, const char *name) {
    if (tracer == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkEventTracer *>(tracer)->getCategoryGroupEnabled(name);
}

const char *SkEventTracer_getCategoryGroupName(reskia_event_tracer_t *tracer, const uint8_t *category_enabled_flag) {
    if (tracer == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkEventTracer *>(tracer)->getCategoryGroupName(category_enabled_flag);
}

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
        uint8_t flags) {
    if (tracer == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkEventTracer *>(tracer)->addTraceEvent(
            phase,
            category_enabled_flag,
            name,
            id,
            num_args,
            arg_names,
            arg_types,
            arg_values,
            flags);
}

void SkEventTracer_updateTraceEventDuration(
        reskia_event_tracer_t *tracer,
        const uint8_t *category_enabled_flag,
        const char *name,
        reskia_event_tracer_handle_t handle) {
    if (tracer == nullptr) {
        return;
    }
    reinterpret_cast<SkEventTracer *>(tracer)->updateTraceEventDuration(
            category_enabled_flag,
            name,
            handle);
}

void SkEventTracer_newTracingSection(reskia_event_tracer_t *tracer, const char *name) {
    if (tracer == nullptr) {
        return;
    }
    reinterpret_cast<SkEventTracer *>(tracer)->newTracingSection(name);
}

} // extern "C"
