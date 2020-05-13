#include <iostream>

#include "ImageCapture/ImageCapture.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int main() {
    ImageCapture imageCapture;

    DXGI_InitCapture(&imageCapture);
    DXGI_StartCapture(&imageCapture, 30,
                      [](unsigned char *data, int size, int width, int height, void *userData) {
                          Mat mat;
                          mat.create(Size(width, height), CV_8UC4);
                          memcpy(mat.data, data, size);
                          Mat cvtMat;
                          cvtColor(mat,cvtMat,COLOR_BGRA2BGR);
                          imwrite("1.png", cvtMat);
                      }, nullptr);

    Sleep(3000);

    DXGI_StopCapture(&imageCapture);
    DXGI_ReleaseCapture(&imageCapture);


    return 0;
}