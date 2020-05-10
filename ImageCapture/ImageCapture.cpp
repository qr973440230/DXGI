#include "ImageCapture.h"
#include <process.h>

#define RESET_OBJECT(A) {if (A) A->Release(); A = NULL;}

/*
 将桌面挂到这个进程中
*/
static bool AttachToThread() {
    HDESK oldDesktop = GetThreadDesktop(GetCurrentThreadId());
    HDESK currentDesktop = OpenInputDesktop(0, FALSE, GENERIC_ALL);
    if (!currentDesktop) {
        return false;
    }

    bool attached = SetThreadDesktop(currentDesktop);
    CloseDesktop(oldDesktop);
    CloseDesktop(currentDesktop);

    return attached;
}

//视频数据捕获函数
static bool ProcessCaptureData(ImageCapture *imageCapture) {
    //将桌面挂到这个进程中
    if (!AttachToThread()) {
        return false;
    }

    ///截取屏幕数据
    IDXGIResource *desktopResource = nullptr;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    HRESULT hr = imageCapture->m_hDeskDup->AcquireNextFrame(0, &frameInfo, &desktopResource);
    if (FAILED(hr)) {
        //
        // 在一些win10的系统上,如果桌面没有变化的情况下，
        // 这里会发生超时现象，但是这并不是发生了错误，而是系统优化了刷新动作导致的。
        // 所以，这里没必要返回FALSE，返回不带任何数据的TRUE即可
        //
        return true;
    }

    //获取纹理2D
    ID3D11Texture2D *acquiredDesktopImage = nullptr;
    hr = desktopResource->QueryInterface(__uuidof(ID3D11Texture2D),
                                         reinterpret_cast<void **>(&acquiredDesktopImage));
    RESET_OBJECT(desktopResource);
    if (FAILED(hr)) {
        return false;
    }

    D3D11_TEXTURE2D_DESC frameDescriptor;
    acquiredDesktopImage->GetDesc(&frameDescriptor);

    //创建一个新的2D纹理对象,用于把 hAcquiredDesktopImage的数据copy进去
    ID3D11Texture2D *newDesktopImage = nullptr;
    frameDescriptor.Usage = D3D11_USAGE_STAGING;
    frameDescriptor.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    frameDescriptor.BindFlags = 0;
    frameDescriptor.MiscFlags = 0;
    frameDescriptor.MipLevels = 1;
    frameDescriptor.ArraySize = 1;
    frameDescriptor.SampleDesc.Count = 1;
    hr = imageCapture->m_hDevice->CreateTexture2D(&frameDescriptor,
                                                  nullptr,
                                                  &newDesktopImage);
    if (FAILED(hr)) {
        RESET_OBJECT(acquiredDesktopImage);
        imageCapture->m_hDeskDup->ReleaseFrame();
        return false;
    }

    ///获取整个帧的数据
    imageCapture->m_hContext->CopyResource((ID3D11Resource *) newDesktopImage,
                                           (ID3D11Resource *) acquiredDesktopImage);
    RESET_OBJECT(acquiredDesktopImage);
    imageCapture->m_hDeskDup->ReleaseFrame();

    // 获取这个2D纹理对象的表面
    IDXGISurface *dxgiSurface = nullptr;
    hr = newDesktopImage->QueryInterface(__uuidof(IDXGISurface),
                                         reinterpret_cast<void **>(&dxgiSurface));
    RESET_OBJECT(newDesktopImage);
    if (FAILED(hr)) {
        return false;
    }

    //映射锁定表面,从而获取表面的数据地址
    //这个时候 mappedRect.pBits 指向的内存就是原始的图像数据, 因为DXGI固定为 32位深度色
    //mappedRect.pBits 指向的就是 BGRA 元数组
    DXGI_MAPPED_RECT mappedRect;
    hr = dxgiSurface->Map(&mappedRect, DXGI_MAP_READ);
    if (SUCCEEDED(hr)) {
        WORD bitsPerPixel = 4;
        int iWidth =
                imageCapture->m_dxOutDesc.DesktopCoordinates.right - imageCapture->m_dxOutDesc.DesktopCoordinates.left;
//        int iHeight = imageCapture->m_dxOutDesc.DesktopCoordinates.bottom - imageCapture->m_dxOutDesc.DesktopCoordinates.top;
        int iCopyDataLength = (imageCapture->m_nWidth * 32 + 31) / 32 * bitsPerPixel;
        int j = 0;
        for (int h = imageCapture->m_nTop; h < imageCapture->m_nTop + imageCapture->m_nHeight; h++) {
            int iSrcOffset = (h * iWidth + imageCapture->m_nLeft) * bitsPerPixel;
            BYTE *pSrc = mappedRect.pBits + iSrcOffset;
            int iDesOffset = (imageCapture->m_nWidth * 32 + 31) / 32 * j * bitsPerPixel;
            BYTE *pDes = (BYTE *) imageCapture->m_memRawBuffer + iDesOffset;
            memcpy(pDes, pSrc, iCopyDataLength);
            j++;
        }

        dxgiSurface->Unmap();
    }

    RESET_OBJECT(dxgiSurface);
    return SUCCEEDED(hr);
}

//视频数据循环捕获线程
static unsigned WINAPI OnImageCaptureThread(void *param) {
    ImageCapture *imageCapture;
    imageCapture = static_cast<ImageCapture *>(param);

    int fps = max(imageCapture->m_fps, 10);
    DWORD dwTimeout = 1000 / fps;

    // 等待超时进入下一次图像数据获取
    while (WaitForSingleObject(imageCapture->m_hStopSignal, dwTimeout) == WAIT_TIMEOUT) {
        if (ProcessCaptureData(imageCapture)) {
            if (imageCapture->m_bActive) {
                //获取图像成功，回调数据给应用层用户处理
                if (imageCapture->m_imageCaptureCallback) {
                    imageCapture->m_imageCaptureCallback((LPBYTE) imageCapture->m_memRawBuffer,
                                                         imageCapture->m_nMemSize,
                                                         imageCapture->m_nWidth,
                                                         imageCapture->m_nHeight,
                                                         imageCapture->m_userData);
                }
            } else {
                // 因为第一帧是黑屏。需要忽略，具体原因未知
                imageCapture->m_bActive = true;
            }
        }
    }

    //关闭信号
    CloseHandle(imageCapture->m_hStopSignal);
    imageCapture->m_hStopSignal = nullptr;

    //关闭线程句柄
    CloseHandle(imageCapture->m_hCaptureThread);
    imageCapture->m_hCaptureThread = nullptr;
    imageCapture->m_bActive = false;

    _endthreadex(0);
    return 0;
}


//开始捕获视频数据
static bool StartImageCapture(ImageCapture *imageCapture) {
    // 释放之前申请的的存放图像的缓存
    free(imageCapture->m_memRawBuffer);
    imageCapture->m_memRawBuffer = nullptr;
    imageCapture->m_nMemSize = 0;

    //计算所需存放图像的缓存大小
    imageCapture->m_nMemSize = imageCapture->m_nWidth * imageCapture->m_nHeight * 4;//获取的图像位图深度32位，所以是*4
    imageCapture->m_memRawBuffer = (char *) malloc(imageCapture->m_nMemSize);
    memset(imageCapture->m_memRawBuffer, 0, imageCapture->m_nMemSize);

    //创建捕获图像的线程
    unsigned int dwThreadId;
    imageCapture->m_hCaptureThread = (HANDLE) _beginthreadex(nullptr,
                                                             0,
                                                             &OnImageCaptureThread,
                                                             imageCapture,
                                                             THREAD_PRIORITY_NORMAL,
                                                             &dwThreadId);
    return imageCapture->m_hCaptureThread != nullptr;
}

// DXGI方式，初始化Capture
bool DXGI_InitCapture(ImageCapture *imageCapture) {
    INT nOutput = 0;
    IDXGIDevice *hDxgiDevice = nullptr;
    IDXGIAdapter *hDxgiAdapter = nullptr;
    IDXGIOutput *hDxgiOutput = nullptr;
    IDXGIOutput1 *hDxgiOutput1 = nullptr;

    //参数初始化
    imageCapture->m_bActive = false;
    imageCapture->m_hCaptureThread = nullptr;
    imageCapture->m_hStopSignal = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    imageCapture->m_memRawBuffer = nullptr;
    imageCapture->m_imageCaptureCallback = nullptr;
    imageCapture->m_userData = nullptr;

    InitializeCriticalSection(&imageCapture->m_csMemLock);

    HRESULT hr = S_OK;
    //Direct3D驱动类型
    D3D_DRIVER_TYPE DriverTypes[] =
            {
                    D3D_DRIVER_TYPE_HARDWARE, //硬件驱动
                    D3D_DRIVER_TYPE_WARP,//软件驱动-性能高
                    D3D_DRIVER_TYPE_REFERENCE, //软件驱动-精度高，速度慢
                    D3D_DRIVER_TYPE_SOFTWARE,//软件驱动-性能低
            };

    UINT NumDriverTypes = ARRAYSIZE(DriverTypes);
    D3D_FEATURE_LEVEL FeatureLevels[] =
            {
                    D3D_FEATURE_LEVEL_11_0,
                    D3D_FEATURE_LEVEL_10_1,
                    D3D_FEATURE_LEVEL_10_0,
                    D3D_FEATURE_LEVEL_9_1
            };

    //初始化D3D设备-m_hDevice
    UINT NumFeatureLevels = ARRAYSIZE(FeatureLevels);
    D3D_FEATURE_LEVEL FeatureLevel;
    for (UINT DriverTypeIndex = 0; DriverTypeIndex < NumDriverTypes; ++DriverTypeIndex) {
        hr = D3D11CreateDevice(nullptr,
                               DriverTypes[DriverTypeIndex],
                               nullptr,
                               0,
                               FeatureLevels,
                               NumFeatureLevels,
                               D3D11_SDK_VERSION,
                               &imageCapture->m_hDevice,
                               &FeatureLevel,
                               &imageCapture->m_hContext);

        if (SUCCEEDED(hr)) {
            break;
        }
    }

    if (FAILED(hr)) {
        DXGI_ReleaseCapture(imageCapture);
        return false;
    }

    hr = imageCapture->m_hDevice->QueryInterface(__uuidof(IDXGIDevice),
                                                 reinterpret_cast<void **>(&hDxgiDevice));
    if (FAILED(hr)) {
        DXGI_ReleaseCapture(imageCapture);
        return false;
    }

    //获取桌面对象描述符-m_dxOutDesc，主要是获取桌面分辨率大小
    hr = hDxgiDevice->GetParent(__uuidof(IDXGIAdapter),
                                reinterpret_cast<void **>(&hDxgiAdapter));
    RESET_OBJECT(hDxgiDevice);

    if (FAILED(hr)) {
        DXGI_ReleaseCapture(imageCapture);
        return false;
    }

    hr = hDxgiAdapter->EnumOutputs(nOutput, &hDxgiOutput);
    RESET_OBJECT(hDxgiAdapter);
    if (FAILED(hr)) {
        DXGI_ReleaseCapture(imageCapture);
        return false;
    }

    hDxgiOutput->GetDesc(&imageCapture->m_dxOutDesc);

    hr = hDxgiOutput->QueryInterface(__uuidof(IDXGIOutput1), reinterpret_cast<void **>(&hDxgiOutput1));
    RESET_OBJECT(hDxgiOutput);
    if (FAILED(hr)) {
        DXGI_ReleaseCapture(imageCapture);
        return false;
    }

    hr = hDxgiOutput1->DuplicateOutput(imageCapture->m_hDevice, &imageCapture->m_hDeskDup);
    RESET_OBJECT(hDxgiOutput1);

    if (FAILED(hr)) {
        DXGI_ReleaseCapture(imageCapture);
        return false;
    }

    return true;
}

bool DXGI_ReleaseCapture(ImageCapture *imageCapture) {
    RESET_OBJECT(imageCapture->m_hDeskDup);
    RESET_OBJECT(imageCapture->m_hContext);
    RESET_OBJECT(imageCapture->m_hDevice);
    free(imageCapture->m_memRawBuffer);
    imageCapture->m_memRawBuffer = nullptr;
    DeleteCriticalSection(&imageCapture->m_csMemLock);

    return true;
}

// DXGI方式，设置视频回调函数，并开始捕获视频数据
bool DXGI_StartCapture(ImageCapture *imageCapture,
                       int fps,
                       int left, int top,
                       int width, int height,
                       ImageCaptureCallback captureCallback,
                       void *userData) {
    imageCapture->m_fps = fps;

    //保存捕获区域参数
    imageCapture->m_nLeft = left;
    imageCapture->m_nTop = top;
    imageCapture->m_nWidth = width;
    imageCapture->m_nHeight = height;

    //设置图像数据回调函数
    imageCapture->m_imageCaptureCallback = captureCallback;
    imageCapture->m_userData = userData;

    bool success = StartImageCapture(imageCapture);
    if (!success) {
        DXGI_ReleaseCapture(imageCapture);
    }

    return success;
}


// 停止视频数据捕获
bool DXGI_StopCapture(ImageCapture *imageCapture) {

    imageCapture->m_imageCaptureCallback = nullptr;
    imageCapture->m_userData = nullptr;

    DXGI_ReleaseCapture(imageCapture);

    return true;
}

