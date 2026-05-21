//
// Created by Codex on 2026/05/21.
//

#include "sk_svg_image.h"

#include "include/core/SkImage.h"
#include "include/core/SkRect.h"
#include "include/core/SkRefCnt.h"
#include "modules/skresources/include/SkResources.h"
#include "modules/svg/include/SkSVGImage.h"
#include "modules/svg/include/SkSVGTypes.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_rect-internal.h"

namespace {

template <typename T, typename Opaque>
T *as_type(const Opaque *value) {
    return const_cast<T *>(reinterpret_cast<const T *>(value));
}

}  // namespace

extern "C" {

bool SkSVGImage_LoadImage(
        reskia_skresources_resource_provider_t *resource_provider,
        const reskia_svg_iri_t *iri,
        const reskia_rect_t *view_port,
        const reskia_svg_preserve_aspect_ratio_t *preserve_aspect_ratio,
        reskia_svg_image_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
    if (resource_provider == nullptr || iri == nullptr || view_port == nullptr || out_info == nullptr) {
        return false;
    }

    sk_sp<skresources::ResourceProvider> provider(
            sk_ref_sp(as_type<skresources::ResourceProvider>(resource_provider)));
    const auto par = preserve_aspect_ratio != nullptr ?
            *as_type<SkSVGPreserveAspectRatio>(preserve_aspect_ratio) :
            SkSVGPreserveAspectRatio();
    SkSVGImage::ImageInfo info = SkSVGImage::LoadImage(
            provider,
            *as_type<SkSVGIRI>(iri),
            *as_type<SkRect>(view_port),
            par);
    if (info.fImage == nullptr) {
        return false;
    }

    out_info->image = static_sk_image_make(std::move(info.fImage));
    out_info->dst = static_sk_rect_make(info.fDst);
    return true;
}

}
