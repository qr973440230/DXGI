//
// Created by qr973 on 2020/5/10.
//

#ifndef DXGI_BMPUTILS_H
#define DXGI_BMPUTILS_H

#include <Windows.h>

__declspec(dllexport) void rotateImg(unsigned char *data, int width, int height);

__declspec(dllexport) void saveBmpFile(const char *fileName, unsigned char *data, int width, int height);

#endif //DXGI_BMPUTILS_H
