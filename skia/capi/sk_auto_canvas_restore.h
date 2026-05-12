//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_AUTO_CANVAS_RESTORE_H
#define RAIA_SKIA_SK_AUTO_CANVAS_RESTORE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * canvas may be NULL.
 * NULL canvas creates a no-op restore guard (SkCanvas * canvas, bool doSave) -> SkAutoCanvasRestore *.
 */
void * SkAutoCanvasRestore_new(void * canvas, bool doSave);
void SkAutoCanvasRestore_delete(void * autoCanvasRestore); // NULL is no-op (SkAutoCanvasRestore *autoCanvasRestore)
/**
 * NULL is no-op.
 * restores at most once (SkAutoCanvasRestore *autoCanvasRestore)
 */
void SkAutoCanvasRestore_restore(void * autoCanvasRestore);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_AUTO_CANVAS_RESTORE_H
