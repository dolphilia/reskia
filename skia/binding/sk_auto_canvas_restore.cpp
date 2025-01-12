//
// Created by dolphilia on 2024/01/05.
//

#include "sk_auto_canvas_restore.h"

#include "include/core/SkCanvas.h"

#ifdef __cplusplus
extern "C" {
#endif

void * SkAutoCanvasRestore_new(void *canvas, bool doSave) {
    return new SkAutoCanvasRestore(static_cast<SkCanvas *>(canvas), doSave);
}

void SkAutoCanvasRestore_delete(void * autoCanvasRestore) {
    delete static_cast<SkAutoCanvasRestore *>(autoCanvasRestore);
}

void SkAutoCanvasRestore_restore(void * autoCanvasRestore) {
    static_cast<SkAutoCanvasRestore *>(autoCanvasRestore)->restore();
}

#ifdef __cplusplus
}
#endif