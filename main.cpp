#include <iostream>

#include "ImageCapture/ImageCapture.h"
#include "Utils/BmpUtils.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int main() {
    ImageCapture imageCapture;

    DXGI_InitCapture(&imageCapture);
    DXGI_StartCapture(&imageCapture, 30,
                      [](unsigned char *data, int size, int width, int height, void *userData) {
                          static int i = 0;
                          char buf[1000];
                          sprintf_s(buf, 1000, "capture%d.bmp", i++);
//                          RotateImg(data, width, height);
                          SaveBmpFile(buf, data, width, height);

//                          std::vector<unsigned char> vector(size);
//                          for (int j = 0; j < size; j++) {
//                              vector.push_back(data[j]);
//                          }
//                          InputArray array((std::vector<unsigned char>()));
//                          imwrite(buf, array);
                      }, nullptr);

    Sleep(1000);

    DXGI_StopCapture(&imageCapture);
    DXGI_ReleaseCapture(&imageCapture);

    return 0;
}