//
// Created by Codex on 2026/05/15.
//

#include "sk_resources.h"

#include "modules/skresources/include/SkResources.h"

#include <utility>

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_matrix-internal.h"
#include "../handles/static_sk_sampling_options-internal.h"
#include "../handles/static_sk_typeface-internal.h"

namespace {

skresources::ImageAsset *as_image_asset(reskia_skresources_image_asset_t *asset) {
    return reinterpret_cast<skresources::ImageAsset *>(asset);
}

skresources::ExternalTrackAsset *as_external_track_asset(reskia_skresources_external_track_asset_t *asset) {
    return reinterpret_cast<skresources::ExternalTrackAsset *>(asset);
}

skresources::ResourceProvider *as_resource_provider(reskia_skresources_resource_provider_t *provider) {
    return reinterpret_cast<skresources::ResourceProvider *>(provider);
}

skresources::MultiFrameImageAsset *as_multi_frame_image_asset(reskia_skresources_image_asset_t *asset) {
    return static_cast<skresources::MultiFrameImageAsset *>(as_image_asset(asset));
}

skresources::FileResourceProvider *as_file_resource_provider(reskia_skresources_resource_provider_t *provider) {
    return static_cast<skresources::FileResourceProvider *>(as_resource_provider(provider));
}

skresources::ImageDecodeStrategy decode_strategy_or_lazy(reskia_skresources_image_decode_strategy_t strategy) {
    switch (strategy) {
        case RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_PRE_DECODE:
            return skresources::ImageDecodeStrategy::kPreDecode;
        case RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE:
        default:
            return skresources::ImageDecodeStrategy::kLazyDecode;
    }
}

reskia_skresources_size_fit_t to_c_size_fit(skresources::ImageAsset::SizeFit fit) {
    switch (fit) {
        case skresources::ImageAsset::SizeFit::kFill:
            return RESKIA_SKRESOURCES_SIZE_FIT_FILL;
        case skresources::ImageAsset::SizeFit::kStart:
            return RESKIA_SKRESOURCES_SIZE_FIT_START;
        case skresources::ImageAsset::SizeFit::kEnd:
            return RESKIA_SKRESOURCES_SIZE_FIT_END;
        case skresources::ImageAsset::SizeFit::kNone:
            return RESKIA_SKRESOURCES_SIZE_FIT_NONE;
        case skresources::ImageAsset::SizeFit::kCenter:
        default:
            return RESKIA_SKRESOURCES_SIZE_FIT_CENTER;
    }
}

reskia_skresources_image_asset_t *release_image_asset(sk_sp<skresources::ImageAsset> asset) {
    return reinterpret_cast<reskia_skresources_image_asset_t *>(asset.release());
}

reskia_skresources_external_track_asset_t *release_external_track_asset(sk_sp<skresources::ExternalTrackAsset> asset) {
    return reinterpret_cast<reskia_skresources_external_track_asset_t *>(asset.release());
}

reskia_skresources_resource_provider_t *release_resource_provider(sk_sp<skresources::ResourceProvider> provider) {
    return reinterpret_cast<reskia_skresources_resource_provider_t *>(provider.release());
}

sk_image_t make_image_handle(sk_sp<SkImage> image) {
    return image ? static_sk_image_make(std::move(image)) : 0;
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    return data ? static_sk_data_make(std::move(data)) : 0;
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    return typeface ? static_sk_typeface_make(std::move(typeface)) : 0;
}

class ReskiaExternalTrackAsset final : public skresources::ExternalTrackAsset {
public:
    ReskiaExternalTrackAsset(
            reskia_skresources_external_track_asset_seek_proc_t seek,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : seek_(seek)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaExternalTrackAsset() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    void seek(float t) override {
        if (seek_ != nullptr) {
            seek_(t, user_data_);
        }
    }

private:
    reskia_skresources_external_track_asset_seek_proc_t seek_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

}  // namespace

extern "C" {

void ImageAsset_ref(reskia_skresources_image_asset_t *asset) {
    if (asset != nullptr) {
        as_image_asset(asset)->ref();
    }
}

void ImageAsset_unref(reskia_skresources_image_asset_t *asset) {
    if (asset != nullptr) {
        as_image_asset(asset)->unref();
    }
}

void ImageAsset_release(reskia_skresources_image_asset_t *asset) {
    ImageAsset_unref(asset);
}

bool ImageAsset_isMultiFrame(reskia_skresources_image_asset_t *asset) {
    return asset != nullptr ? as_image_asset(asset)->isMultiFrame() : false;
}

sk_image_t ImageAsset_getFrame(reskia_skresources_image_asset_t *asset, float t) {
    return asset != nullptr ? make_image_handle(as_image_asset(asset)->getFrame(t)) : 0;
}

bool ImageAsset_getFrameData(reskia_skresources_image_asset_t *asset, float t, reskia_skresources_frame_data_t *out_frame_data) {
    if (out_frame_data != nullptr) {
        out_frame_data->image = 0;
        out_frame_data->sampling = 0;
        out_frame_data->matrix = 0;
        out_frame_data->scaling = RESKIA_SKRESOURCES_SIZE_FIT_CENTER;
    }
    if (asset == nullptr || out_frame_data == nullptr) {
        return false;
    }

    skresources::ImageAsset::FrameData frame_data = as_image_asset(asset)->getFrameData(t);
    out_frame_data->image = make_image_handle(std::move(frame_data.image));
    out_frame_data->sampling = static_sk_sampling_options_make(frame_data.sampling);
    out_frame_data->matrix = static_sk_matrix_make(frame_data.matrix);
    out_frame_data->scaling = to_c_size_fit(frame_data.scaling);
    return true;
}

reskia_skresources_external_track_asset_t *ExternalTrackAsset_new(
        reskia_skresources_external_track_asset_seek_proc_t seek,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skresources_external_track_asset_t *>(
            new ReskiaExternalTrackAsset(seek, user_data, release_proc));
}

void ExternalTrackAsset_ref(reskia_skresources_external_track_asset_t *asset) {
    if (asset != nullptr) {
        as_external_track_asset(asset)->ref();
    }
}

void ExternalTrackAsset_unref(reskia_skresources_external_track_asset_t *asset) {
    if (asset != nullptr) {
        as_external_track_asset(asset)->unref();
    }
}

void ExternalTrackAsset_release(reskia_skresources_external_track_asset_t *asset) {
    ExternalTrackAsset_unref(asset);
}

void ExternalTrackAsset_seek(reskia_skresources_external_track_asset_t *asset, float t) {
    if (asset != nullptr) {
        as_external_track_asset(asset)->seek(t);
    }
}

reskia_skresources_image_asset_t *MultiFrameImageAsset_Make(sk_data_t data, reskia_skresources_image_decode_strategy_t strategy) {
    return release_image_asset(skresources::MultiFrameImageAsset::Make(
            static_sk_data_get_entity(data),
            decode_strategy_or_lazy(strategy)));
}

bool MultiFrameImageAsset_isMultiFrame(reskia_skresources_image_asset_t *asset) {
    return asset != nullptr ? as_multi_frame_image_asset(asset)->isMultiFrame() : false;
}

float MultiFrameImageAsset_duration(reskia_skresources_image_asset_t *asset) {
    return asset != nullptr ? as_multi_frame_image_asset(asset)->duration() : 0.0f;
}

sk_image_t MultiFrameImageAsset_getFrame(reskia_skresources_image_asset_t *asset, float t) {
    return asset != nullptr ? make_image_handle(as_multi_frame_image_asset(asset)->getFrame(t)) : 0;
}

void ResourceProvider_ref(reskia_skresources_resource_provider_t *provider) {
    if (provider != nullptr) {
        as_resource_provider(provider)->ref();
    }
}

void ResourceProvider_unref(reskia_skresources_resource_provider_t *provider) {
    if (provider != nullptr) {
        as_resource_provider(provider)->unref();
    }
}

void ResourceProvider_release(reskia_skresources_resource_provider_t *provider) {
    ResourceProvider_unref(provider);
}

sk_data_t ResourceProvider_load(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[]) {
    return provider != nullptr ? make_data_handle(as_resource_provider(provider)->load(resource_path, resource_name)) : 0;
}

reskia_skresources_image_asset_t *ResourceProvider_loadImageAsset(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[], const char resource_id[]) {
    return provider != nullptr ? release_image_asset(as_resource_provider(provider)->loadImageAsset(resource_path, resource_name, resource_id)) : nullptr;
}

sk_data_t ResourceProvider_loadFont(reskia_skresources_resource_provider_t *provider, const char name[], const char url[]) {
    return provider != nullptr ? make_data_handle(as_resource_provider(provider)->loadFont(name, url)) : 0;
}

sk_typeface_t ResourceProvider_loadTypeface(reskia_skresources_resource_provider_t *provider, const char name[], const char url[]) {
    return provider != nullptr ? make_typeface_handle(as_resource_provider(provider)->loadTypeface(name, url)) : 0;
}

reskia_skresources_external_track_asset_t *ResourceProvider_loadAudioAsset(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[], const char resource_id[]) {
    return provider != nullptr ? release_external_track_asset(as_resource_provider(provider)->loadAudioAsset(resource_path, resource_name, resource_id)) : nullptr;
}

reskia_skresources_resource_provider_t *FileResourceProvider_Make(const char base_dir[], reskia_skresources_image_decode_strategy_t strategy) {
    if (base_dir == nullptr) {
        return nullptr;
    }
    return release_resource_provider(skresources::FileResourceProvider::Make(
            SkString(base_dir),
            decode_strategy_or_lazy(strategy)));
}

sk_data_t FileResourceProvider_load(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[]) {
    return provider != nullptr ? make_data_handle(as_file_resource_provider(provider)->load(resource_path, resource_name)) : 0;
}

reskia_skresources_image_asset_t *FileResourceProvider_loadImageAsset(reskia_skresources_resource_provider_t *provider, const char resource_path[], const char resource_name[], const char resource_id[]) {
    return provider != nullptr ? release_image_asset(as_file_resource_provider(provider)->loadImageAsset(resource_path, resource_name, resource_id)) : nullptr;
}

reskia_skresources_resource_provider_t *CachingResourceProvider_Make(reskia_skresources_resource_provider_t *provider) {
    return provider != nullptr ? release_resource_provider(skresources::CachingResourceProvider::Make(sk_ref_sp(as_resource_provider(provider)))) : nullptr;
}

reskia_skresources_resource_provider_t *DataURIResourceProviderProxy_Make(reskia_skresources_resource_provider_t *provider, reskia_skresources_image_decode_strategy_t strategy, sk_font_mgr_t font_mgr) {
    return release_resource_provider(skresources::DataURIResourceProviderProxy::Make(
            provider != nullptr ? sk_ref_sp(as_resource_provider(provider)) : nullptr,
            decode_strategy_or_lazy(strategy),
            static_sk_font_mgr_get_entity(font_mgr)));
}

}
