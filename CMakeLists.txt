cmake_minimum_required(VERSION 3.15)

project(DXGI)

set(CMAKE_CXX_STANDARD 14)

#设置exe 输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#设置lib dll输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(ImageCapture)
add_subdirectory(Utils)

add_executable(DXGI main.cpp)

target_link_libraries(DXGI DXGIUtils DXGIImageCapture)