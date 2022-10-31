//
// Created by Ilya @yurnerox Rakin on 26.10.22.
//

#include "image.h"

struct image rotate_90(struct image const *img) {
    struct image new_image = create_image(img->height, img->width);
    for (uint32_t i = 0; i < img->height; i++) {
        for (uint32_t j = 0; j < img->width; j++) {
            new_image.data[j * img->height + img->height - i - 1] = img->data[i * img->width + j];
        }
    }
    return new_image;
}
