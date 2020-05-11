#ifndef IMAGE_CAPTURE_H
#define IMAGE_CAPTURE_H

#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>

typedef void(*ImageCaptureCallback)(unsigned char *data, int size, int width, int height, void *user_data);

typedef struct {
    int m_nWidth;//捕获区域-宽度
    int m_nHeight;//捕获区域-高度
    int m_fps;// 捕获帧率

    bool m_bActive;//是否激活，即是否获取到视频帧
    HANDLE m_hCaptureThread;//捕获线程句柄
    HANDLE m_hStopSignal;//线程停止信号

    CRITICAL_SECTION m_csMemLock;//数据访问互斥锁
    void *m_memRawBuffer;//RGB数据存放缓冲区
    int m_nMemSize;//RGB数据缓冲区大小

    ID3D11Device *m_hDevice;//设备对象
    ID3D11DeviceContext *m_hContext;//设备上下文
    IDXGIOutputDuplication *m_hDeskDup;//桌面对象
    DXGI_OUTPUT_DESC m_dxOutDesc;//桌面对象描述-保存了桌面分辨率等信息

    ImageCaptureCallback m_imageCaptureCallback;//实时捕获数据回调函数
    void *m_userData;
} ImageCapture;


__declspec(dllexport) bool DXGI_InitCapture(ImageCapture *imageCapture);

__declspec(dllexport) bool DXGI_ReleaseCapture(ImageCapture *imageCapture);

__declspec(dllexport) bool DXGI_StartCapture(ImageCapture *imageCapture,
                                             int fps,
                                             ImageCaptureCallback captureCallback,
                                             void *userData);

__declspec(dllexport) bool DXGI_StopCapture(ImageCapture *imageCapture);

#endif //IMAGE_CAPTURE_H
