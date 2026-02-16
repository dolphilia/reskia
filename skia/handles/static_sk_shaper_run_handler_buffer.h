//
// Created by dolphilia on 2026/02/17.
//

#ifndef RAIA_SKIA_STATIC_SK_SHAPER_RUN_HANDLER_BUFFER_H
#define RAIA_SKIA_STATIC_SK_SHAPER_RUN_HANDLER_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_shaper_run_handler_buffer_t;
void static_sk_shaper_run_handler_buffer_delete(int key);
void * static_sk_shaper_run_handler_buffer_get_ptr(int key); // -> SkShaper::RunHandler::Buffer *
#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_STATIC_SK_SHAPER_RUN_HANDLER_BUFFER_H
