//
// Created by qr973 on 2020/5/10.
//

#include "BmpUtils.h"

void RotateImg(unsigned char *data, int width, int height) {
    unsigned int *imgData;
    unsigned int *imgDataR;
    unsigned int *imgDataTmp;

    imgDataR = imgData = (unsigned int *) data;

    int count = width * height;
    imgDataTmp = new unsigned int[count];
    for (int i = 0; i < count; ++i) {
        imgDataTmp[i] = imgData[count - i - 1];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            imgDataR[j + i * width] = imgDataTmp[width - j - 1 + i * width];
        }
    }

    delete[] imgDataTmp;
}

void SaveBmpFile(const char *fileName, unsigned char *data, int width, int height) {
    int imgLength = width * height * 4;

    BITMAPFILEHEADER tagBitmapFileHeader;
    memset(&tagBitmapFileHeader, 0, sizeof(tagBitmapFileHeader));
    tagBitmapFileHeader.bfType = 0x4d42;     //图像格式。必须为'BM'格式。
    tagBitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); //从文件开头到数据的偏移量
    tagBitmapFileHeader.bfSize = imgLength + tagBitmapFileHeader.bfOffBits;//文件大小

    BITMAPINFOHEADER bmInfo;
    memset(&bmInfo, 0, sizeof(bmInfo));
    bmInfo.biSize = sizeof(bmInfo);
    bmInfo.biWidth = width;
    bmInfo.biHeight = height;
    bmInfo.biPlanes = 1;
    bmInfo.biBitCount = 32;
    bmInfo.biCompression = BI_RGB;

    HANDLE file = CreateFileA(fileName,
                              GENERIC_WRITE,
                              0,
                              nullptr,
                              CREATE_ALWAYS,
                              0,
                              nullptr);

    if (file != INVALID_HANDLE_VALUE) {
        DWORD dwWritten;
        WriteFile(file,
                  &tagBitmapFileHeader,
                  sizeof(BITMAPFILEHEADER),
                  &dwWritten,
                  nullptr);
        WriteFile(file,
                  &bmInfo,
                  sizeof(BITMAPINFOHEADER),
                  &dwWritten,
                  nullptr);
        WriteFile(file,
                  data,
                  imgLength,
                  &dwWritten,
                  nullptr);
        CloseHandle(file);
    }
}
