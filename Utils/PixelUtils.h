//
// Created by qr973 on 2020/5/11.
//

#ifndef DXGI_PIXELUTILS_H
#define DXGI_PIXELUTILS_H


__declspec(dllexport) void RGBAToRGB(const unsigned char *src, unsigned char *dst, int numPixels);

__declspec(dllexport) void RGBAToBGRA(const unsigned char *src, unsigned char *dst, int numPixels);

__declspec(dllexport) void BGRAToBGR(const unsigned char *src, unsigned char *dst, int numPixels);

#endif //DXGI_PIXELUTILS_H
