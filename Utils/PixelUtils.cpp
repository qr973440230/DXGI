//
// Created by qr973 on 2020/5/11.
//

#include "PixelUtils.h"

void RGBAToRGB(const unsigned char *src, unsigned char *dst, int numPixels) {
    int col;

    for (col = 0; col < numPixels; col++, src += 4, dst += 3) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
    }
}

void RGBAToBGRA(const unsigned char *src, unsigned char *dst, int numPixels) {
    int col;

    for (col = 0; col < numPixels; col++, src += 4, dst += 4) {
        dst[0] = src[2];
        dst[1] = src[1];
        dst[2] = src[0];
        dst[3] = src[3];
    }
}

void BGRAToBGR(const unsigned char *src, unsigned char *dst, int numPixels) {
    int col;

    for (col = 0; col < numPixels; col++, src += 4, dst += 3) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
    }
}


