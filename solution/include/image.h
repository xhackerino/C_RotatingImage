//
// Created by Ilya @Ilya @yurnerox Rakin Rakin on 26.10.22.
//

#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H

#include <stdint.h>

struct pixel { uint8_t b, g, r; };

struct image {
    uint32_t width;
    uint32_t height;
    struct pixel *data;
};

struct image create_image(uint32_t width, uint32_t height);

#endif //IMAGE_TRANSFORMER_IMAGE_H
