#ifndef IMAGE_CAPTURE_H
#define IMAGE_CAPTURE_H

#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>

typedef void(*ImageCaptureCallback)(unsigned char *data, int size, int width, int height, void *user_data);

typedef struct {
    int m_nWidth;//捕获区域-宽度
    int m_nHeight;//捕获区域-高度
    int m_nFps;// 捕获帧率
    int m_nMemSize;//RGB数据缓冲区大小

    bool m_bActive;//是否激活，即是否获取到视频帧
    HANDLE m_hCaptureThread;//捕获线程句柄
    HANDLE m_hStopSignal;//线程停止信号

    ID3D11Device *m_hDevice;//设备对象
    ID3D11DeviceContext *m_hContext;//设备上下文
    IDXGIOutputDuplication *m_hDeskDup;//桌面对象
    DXGI_OUTPUT_DESC m_hOutDesc;//桌面对象描述-保存了桌面分辨率等信息
    DXGI_OUTDUPL_DESC m_hDuplDesc;// 输出的尺寸以及包含桌面图像的表面，桌面映像的格式始终为DXGI_FORMAT_B8G8R8A8_UNORM。

    ImageCaptureCallback m_imageCaptureCallback;//实时捕获数据回调函数
    void *m_userData;
} ImageCapture;


/*
 * 初始化ImageCapture 只应该调用一次
 */
__declspec(dllexport) bool DXGI_InitCapture(ImageCapture *imageCapture);

/*
 * 释放ImageCapture 资源 应该与Init成对出现
 */
__declspec(dllexport) bool DXGI_ReleaseCapture(ImageCapture *imageCapture);

/*
 * 开始捕获函数，captureCallback将在捕获线程中执行
 */
__declspec(dllexport) bool DXGI_StartCapture(ImageCapture *imageCapture,
                                             int fps,
                                             ImageCaptureCallback captureCallback,
                                             void *userData);

/*
 * 停止捕获函数
 */
__declspec(dllexport) bool DXGI_StopCapture(ImageCapture *imageCapture);

#endif //IMAGE_CAPTURE_H
