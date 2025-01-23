//
// Created by dolphilia on 2024/01/13.
//

#include "sk_malloc_pixel_ref.h"

#include "include/core/SkPixelRef.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkData.h"
#include "include/core/SkMallocPixelRef.h"

#include "../static/static_sk_pixel_ref.h"
#include "../static/static_sk_data.h"

#include "../static/static_sk_pixel_ref-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

sk_pixel_ref_t SkMallocPixelRef_MakeAllocate(const void *imageInfo, size_t rowBytes) {
    return static_sk_pixel_ref_make(SkMallocPixelRef::MakeAllocate(* static_cast<const SkImageInfo *>(imageInfo), rowBytes));
}

sk_pixel_ref_t SkMallocPixelRef_MakeWithData(const void *imageInfo, size_t rowBytes, sk_data_t data) {
    return static_sk_pixel_ref_make(SkMallocPixelRef::MakeWithData(* static_cast<const SkImageInfo *>(imageInfo), rowBytes, static_sk_data_move(data)));
}

}
