#include <iostream>

#include "ImageCapture/ImageCapture.h"
#include "Utils/BmpUtils.h"

int main() {
    ImageCapture imageCapture;

    DXGI_InitCapture(&imageCapture);
    DXGI_StartCapture(&imageCapture, 30, 0, 0, 1920, 1080,
                      [](unsigned char *data, int size, int width, int height, void *userData) {
                          static int i = 0;
                          char buf[1000];
                          sprintf_s(buf, 1000, "capture%d.bmp", i++);
                          rotateImg(data, width, height);
                          saveBmpFile(buf, data, width, height);
                      }, nullptr);

    Sleep(10000);

    DXGI_ReleaseCapture(&imageCapture);

    return 0;
}