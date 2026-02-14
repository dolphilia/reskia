#ifndef STATIC_SK_IMAGE_GENERATOR_INTERNAL_H
#define STATIC_SK_IMAGE_GENERATOR_INTERNAL_H
#include <set>
#include <map>
#include "include/core/SkImageGenerator.h"
#ifdef _WIN32
#include <memory>
#endif
int static_sk_image_generator_make(std::unique_ptr<SkImageGenerator> value);
void static_sk_image_generator_set(int key, std::unique_ptr<SkImageGenerator> value);
SkImageGenerator* static_sk_image_generator_borrow_entity(int key);
std::unique_ptr<SkImageGenerator> static_sk_image_generator_take_entity(int key);
std::unique_ptr<SkImageGenerator> static_sk_image_generator_get_entity(int key);
#endif // STATIC_SK_IMAGE_GENERATOR_INTERNAL_H
