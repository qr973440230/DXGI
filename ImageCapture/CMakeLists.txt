cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

add_library(DXGIImageCapture
        SHARED
        ImageCapture.cpp
        ImageCapture.h
        )

target_link_libraries(DXGIImageCapture
        d3d11
        dxgi)

