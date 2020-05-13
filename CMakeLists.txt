cmake_minimum_required(VERSION 3.15)

project(DXGI)

set(CMAKE_CXX_STANDARD 14)

#设置exe 输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#设置lib dll输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(ThreePartLibraries/include/)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
        link_directories(ThreePartLibraries/lib/x64/debug)
        add_custom_target(copy_runtime ALL
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/ThreePartLibraries/shared/x64/debug" "${CMAKE_BINARY_DIR}"
                )

    else ()
        link_directories(ThreePartLibraries/lib/x64/release)
        add_custom_target(copy_runtime ALL
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/ThreePartLibraries/shared/x64/release" "${CMAKE_BINARY_DIR}"
                )
    endif ()
else ()
    if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
        link_directories(ThreePartLibraries/lib/x86/debug)
        add_custom_target(copy_runtime ALL
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/ThreePartLibraries/shared/x86/debug" "${CMAKE_BINARY_DIR}"
                )
    else ()
        link_directories(ThreePartLibraries/lib/x86/release)
        add_custom_target(copy_runtime ALL
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/ThreePartLibraries/shared/x86/release" "${CMAKE_BINARY_DIR}"
                )
    endif ()
endif ()

add_subdirectory(ImageCapture)
add_subdirectory(Utils)

add_executable(DXGI main.cpp)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(OPCVLIBNAME opencv_world430d)
else ()
    set(OPCVLIBNAME opencv_world430)
endif ()
target_link_libraries(DXGI DXGIUtils DXGIImageCapture ${OPCVLIBNAME})
add_dependencies(DXGI copy_runtime)

add_executable(MatchTemplate matchTemplate.cpp)
target_link_libraries(MatchTemplate ${OPCVLIBNAME})
add_dependencies(MatchTemplate copy_runtime)
