#include "bmp.h"
#include "image.h"
#include "rotation.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc == 3) {
        FILE *input = fopen(argv[1], "rb");
        if (input == NULL) { return 1; }
        FILE *output = fopen(argv[2], "wb");
        if (output == NULL) { return 1; }

        struct image img;

        enum read_status readStatus = from_bmp(input, &img);
        if (readStatus != READ_OK) { return 1; }

        struct image new_image = rotate_90(&img);

        enum write_status writeStatus = to_bmp(output, &new_image);
        if (writeStatus != WRITE_OK) { return 1; }

        free(img.data);
        free(new_image.data);

        fclose(input);
        fclose(output);
    } else {
        return 1;
    }
    return 0;
}
