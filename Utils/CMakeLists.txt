cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

add_library(DXGIUtils
        SHARED
        BmpUtils.cpp
        BmpUtils.h)
