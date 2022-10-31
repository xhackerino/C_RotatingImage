//
// Created by Ilya @yurnerox Rakin on 26.10.22.
//
#include "image.h"
#include <stdint.h>
#include <stdlib.h>


struct image create_image(uint32_t width, uint32_t height) {
    struct image img;
    img.width = width;
    img.height = height;
    img.data = malloc(width * height * sizeof(struct pixel));
    return img;
}
