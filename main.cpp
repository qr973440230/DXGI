#include <iostream>

#include "ImageCapture/ImageCapture.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int main() {
    ImageCapture imageCapture;

    DXGI_InitCapture(&imageCapture);
    DXGI_StartCapture(&imageCapture, 60,
                      [](unsigned char *data, int size, int width, int height, void *userData) {
                          static int i = 0;
                          char buf[100];
                          sprintf_s(buf, 100, "%d.png", i++);
                          printf("%s \n", buf);

                          Mat mat;
                          mat.create(Size(width, height), CV_8UC4);
                          memcpy(mat.data, data, size);

                          Mat cvtMat;
                          cvtColor(mat, cvtMat, COLOR_BGRA2BGR);
                          imwrite(buf, cvtMat);

                      }, nullptr);

    Sleep(1000);

    DXGI_StopCapture(&imageCapture);
    DXGI_ReleaseCapture(&imageCapture);

    return 0;
}