//
// Created by Ilya @yurnerox Rakin on 26.10.22.
//
#include "bmp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


uint32_t get_padding(uint32_t width) {
    uint32_t padding = 0;
    if (width % 4 != 0) {
        padding = 4 - (width * 3) % 4;
    }
    return padding;
}

struct bmp_header make_header(uint32_t width, uint32_t height) {
    struct bmp_header header;
    uint32_t padding = get_padding(width);
    header.bfType = 0x4D42;
    header.bfileSize = 14 + 40 + (width * 3 + padding) * height;
    header.bfReserved = 0;
    header.bOffBits = 14 + 40;
    header.biSize = 40;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = (width * 3 + padding) * height;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    return header;
}

enum read_status from_bmp(FILE *in, struct image *img) {
    struct bmp_header header;
    fread(&header, sizeof(struct bmp_header), 1, in);
    if (header.bfType != 0x4D42) { return READ_INVALID_SIGNATURE; }
    if (header.biBitCount != 24) { return READ_INVALID_BITS; }
    if (header.biCompression != 0) { return READ_INVALID_HEADER; }
    uint32_t width = header.biWidth;
    uint32_t height = header.biHeight;
    uint32_t padding = get_padding(width);
    img->width = width;
    img->height = height;
    img->data = malloc(width * height * sizeof(struct pixel));
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            fread(&img->data[i * width + j], sizeof(struct pixel), 1, in);
        }
        fseek(in, padding, SEEK_CUR);
    }
    return READ_OK;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
    struct bmp_header header = make_header(img->width, img->height);
    fwrite(&header, sizeof(struct bmp_header), 1, out);
    uint32_t width = img->width;
    uint32_t height = img->height;
    uint32_t padding = get_padding(width);
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            fwrite(&img->data[i * width + j], sizeof(struct pixel), 1, out);
        }
        for (uint32_t k = 0; k < padding; k++) {
            uint8_t zero = 0;
            fwrite(&zero, sizeof(uint8_t), 1, out);
        }
    }
    return WRITE_OK;
}
