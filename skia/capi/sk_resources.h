//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_RESOURCES_H
#define RAIA_SKIA_SK_RESOURCES_H

#include <stdbool.h>
#include <stdint.h>

#include "reskia_callback.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_sampling_options.h"
#include "../handles/static_sk_typeface.h"

typedef struct reskia_skresources_image_asset_t reskia_skresources_image_asset_t;
typedef struct reskia_skresources_external_track_asset_t reskia_skresources_external_track_asset_t;
typedef struct reskia_skresources_resource_provider_t reskia_skresources_resource_provider_t;

typedef int32_t reskia_skresources_image_decode_strategy_t;
typedef int32_t reskia_skresources_size_fit_t;

typedef struct reskia_skresources_frame_data_t {
    sk_image_t image;
    sk_sampling_options_t sampling;
    sk_matrix_t matrix;
    reskia_skresources_size_fit_t scaling;
} reskia_skresources_frame_data_t;

typedef void (*reskia_skresources_external_track_asset_seek_proc_t)(
        float t,
        void *user_data);

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE = 0,
    RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_PRE_DECODE = 1,
};

enum {
    RESKIA_SKRESOURCES_SIZE_FIT_FILL = 0,
    RESKIA_SKRESOURCES_SIZE_FIT_START = 1,
    RESKIA_SKRESOURCES_SIZE_FIT_CENTER = 2,
    RESKIA_SKRESOURCES_SIZE_FIT_END = 3,
    RESKIA_SKRESOURCES_SIZE_FIT_NONE = 4,
};

void ImageAsset_ref(reskia_skresources_image_asset_t *asset); // NULL input is no-op.
void ImageAsset_unref(reskia_skresources_image_asset_t *asset); // NULL input is no-op.
void ImageAsset_release(reskia_skresources_image_asset_t *asset); // NULL input is no-op.
bool ImageAsset_isMultiFrame(reskia_skresources_image_asset_t *asset); // NULL input returns false.
sk_image_t ImageAsset_getFrame(reskia_skresources_image_asset_t *asset, float t); // returned handle owns a ref; 0 when unavailable.
bool ImageAsset_getFrameData(reskia_skresources_image_asset_t *asset, float t, reskia_skresources_frame_data_t *out_frame_data); // output handles are caller-owned.

reskia_skresources_external_track_asset_t *ExternalTrackAsset_new(reskia_skresources_external_track_asset_seek_proc_t seek, void *user_data, reskia_callback_release_proc_t release_proc);
void ExternalTrackAsset_ref(reskia_skresources_external_track_asset_t *asset); // NULL input is no-op.
void ExternalTrackAsset_unref(reskia_skresources_external_track_asset_t *asset); // NULL input is no-op.
void ExternalTrackAsset_release(reskia_skresources_external_track_asset_t *asset); // NULL input is no-op.
void ExternalTrackAsset_seek(reskia_skresources_external_track_asset_t *asset, float t); // NULL input is no-op.

reskia_skresources_image_asset_t *MultiFrameImageAsset_Make(sk_data_t data, reskia_skresources_image_decode_strategy_t strategy); // data is borrowed; NULL/invalid data returns NULL.
bool MultiFrameImageAsset_isMultiFrame(reskia_skresources_image_asset_t *asset); // NULL input returns false.
sk_image_t MultiFrameImageAsset_getFrame(reskia_skresources_image_asset_t *asset, float t); // returned handle owns a ref; 0 when unavailable.

void ResourceProvider_ref(reskia_skresources_resource_provider_t *provider); // NULL input is no-op.
void ResourceProvider_unref(reskia_skresources_resource_provider_t *provider); // NULL input is no-op.
void ResourceProvider_release(reskia_skresources_resource_provider_t *provider); // NULL input is no-op.
sk_data_t ResourceProvider_load(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[]); // returned handle owns a ref; 0 when unavailable.
reskia_skresources_image_asset_t *ResourceProvider_loadImageAsset(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[], const char resource_id[]); // returned pointer owns a ref; release with ImageAsset_release.
sk_data_t ResourceProvider_loadFont(reskia_skresources_resource_provider_t *provider, const char name[], const char url[]); // returned handle owns a ref; 0 when unavailable.
sk_typeface_t ResourceProvider_loadTypeface(reskia_skresources_resource_provider_t *provider, const char name[], const char url[]); // returned handle owns a ref; 0 when unavailable.
reskia_skresources_external_track_asset_t *ResourceProvider_loadAudioAsset(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[], const char resource_id[]); // returned pointer owns a ref; release with ExternalTrackAsset_release.

reskia_skresources_resource_provider_t *FileResourceProvider_Make(const char base_dir[], reskia_skresources_image_decode_strategy_t strategy); // base_dir must name an existing directory.
sk_data_t FileResourceProvider_load(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[]);
reskia_skresources_image_asset_t *FileResourceProvider_loadImageAsset(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[], const char resource_id[]);

reskia_skresources_resource_provider_t *CachingResourceProvider_Make(reskia_skresources_resource_provider_t *provider); // provider is borrowed and retained; NULL returns NULL.
reskia_skresources_resource_provider_t *DataURIResourceProviderProxy_Make(reskia_skresources_resource_provider_t *provider, reskia_skresources_image_decode_strategy_t strategy, sk_font_mgr_t font_mgr); // provider/font_mgr are borrowed and retained when present.

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_RESOURCES_H
