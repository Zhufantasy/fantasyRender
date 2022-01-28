cmake_minimum_required(VERSION 3.14)

project(fantasyRender)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CONFIGURATION_TYPES "Release")

set(HEADERS
        type.h
        camera.h
        light.h
        mesh.h
        OBJ_Loader.h
        scene.h
        shader.h
        texture.h
        tgaimage.h
        rasterization.h
        )

set(SOURCES
        camera.cpp
        main.cpp
        mesh.cpp
        rasterization.cpp
        scene.cpp
        shader.cpp
        texture.cpp
        tgaimage.cpp
        type.cpp
        )

if(WIN32)
    set(HEADERS ${HEADERS} platform/windows/window.h)
    set(SOURCES ${SOURCES} platform/windows/window_windows.cpp)
# else()
#     set(HEADERS ${HEADERS} platform/linux/window.h)
#     set(SOURCES ${SOURCES} platform/linux/window_linux.cpp)
endif()

add_executable(fantasyRender  ${HEADERS} ${SOURCES})

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT fantasyRender)
source_group(TREE "${CMAKE_SOURCE_DIR}" FILES ${HEADERS} ${SOURCES})