cmake_minimum_required(VERSION 3.28)
project(AudioPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:/Qt/6.8.0/mingw_64")
set(FFMPEG_DIR "C:/src/ffmpeg")
include_directories("${FFMPEG_DIR}/include")

# 链接 FFmpeg 库
link_directories("${FFMPEG_DIR}/lib")

# 查找 FFmpeg 库
find_library(AVCODEC_LIB avcodec HINTS "${FFMPEG_DIR}/lib")
find_library(AVFORMAT_LIB avformat HINTS "${FFMPEG_DIR}/lib")
find_library(AVUTIL_LIB avutil HINTS "${FFMPEG_DIR}/lib")
find_library(SWSCALE_LIB swscale HINTS "${FFMPEG_DIR}/lib")
find_library(SWRESAMPLE_LIB swresample HINTS "${FFMPEG_DIR}/lib")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(AudioPlayer main.cpp
        widget.cpp
        widget.h
        widget.ui
        playthread.cpp
        playthread.h
)
target_link_libraries(AudioPlayer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Multimedia
        ${AVCODEC_LIB} ${AVFORMAT_LIB} ${AVUTIL_LIB} ${SWSCALE_LIB} ${SWRESAMPLE_LIB}
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
