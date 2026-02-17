#include <cstdio>

#import <Metal/Metal.h>

#include "capi/sk_gpu_context.h"
#include "capi/sk_graphics.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[gpu-context-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_context_create_destroy() {
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    if (device == nil) {
        std::fprintf(stdout, "[gpu-context-capi-smoke] SKIP: Metal device is unavailable in this environment\n");
        return true;
    }

    id<MTLCommandQueue> queue = [device newCommandQueue];
    if (queue == nil) {
        std::fprintf(stdout, "[gpu-context-capi-smoke] SKIP: Metal command queue could not be created\n");
        return true;
    }

    bool exercised = false;

#if RESKIA_TEST_GPU_GANESH
    {
        reskia_direct_context_t* direct_context =
                Reskia_GaneshContext_MakeMetal((void*)device, (void*)queue);
        if (!check(direct_context != nullptr, "Reskia_GaneshContext_MakeMetal")) {
            return false;
        }
        Reskia_DirectContext_FlushAndSubmit(direct_context, true);
        Reskia_DirectContext_Release(direct_context);
        exercised = true;
    }
#endif

#if RESKIA_TEST_GPU_GRAPHITE
    {
        reskia_graphite_context_t* graphite_context =
                Reskia_GraphiteContext_MakeMetal((void*)device, (void*)queue);
        if (!check(graphite_context != nullptr, "Reskia_GraphiteContext_MakeMetal")) {
            return false;
        }

        reskia_graphite_recorder_t* recorder =
                Reskia_GraphiteContext_MakeRecorder(graphite_context);
        if (!check(recorder != nullptr, "Reskia_GraphiteContext_MakeRecorder")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }

        Reskia_GraphiteRecorder_Release(recorder);
        Reskia_GraphiteContext_Release(graphite_context);
        exercised = true;
    }
#endif

    return check(exercised, "no GPU context path exercised");
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_context_create_destroy()) {
        return 1;
    }

    std::fprintf(stdout, "[gpu-context-capi-smoke] PASS\n");
    return 0;
}
