cmake_minimum_required(VERSION 3.20)
project(qt5demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/msvc2019_64")

SET(FFMPEG_LIB_DIRS  ${PROJECT_SOURCE_DIR}/libs/ffmpeg-n5.1)
SET(SDL2_LIB_DIRS  ${PROJECT_SOURCE_DIR}/libs/SDL2-2.0.22)

SET(AVCODEC_LIBRARY ${FFMPEG_LIB_DIRS}/lib/avcodec.lib)
SET(AVFORMAT_LIBRARY ${FFMPEG_LIB_DIRS}/lib/avformat.lib)
SET(AVUTIL_LIBRARY  ${FFMPEG_LIB_DIRS}/lib/avutil.lib)
SET(AVDEVICE_LIBRARY  ${FFMPEG_LIB_DIRS}/lib/avdevice.lib)


SET(SDL2TEST_LIBRARY ${SDL2_LIB_DIRS}/lib/x64/SDL2test.lib)
SET(SDL2_LIBRARY ${SDL2_LIB_DIRS}/lib/x64/SDL2.lib)
SET(SDL2MAIN_LIBRARY  ${SDL2_LIB_DIRS}//lib/x64/SDL2main.lib)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt5demo
        main.cpp
        videopaly/Videoplay.cpp
        videopaly/Videoplay.h
        decoder/Decoder.cpp
        decoder/Decoder.h)

include_directories(
        ${FFMPEG_LIB_DIRS}/include
        ${SDL2_LIB_DIRS}/include
)
file(GLOB SDL2dll_src "${SDL2_LIB_DIRS}/lib/x64/*.dll" )
file(GLOB FFMPEGdll_src "${FFMPEG_LIB_DIRS}/bin/*.dll" )

file(COPY ${SDL2dll_src} DESTINATION ".")
file(COPY ${FFMPEGdll_src} DESTINATION  ".")

target_link_libraries(qt5demo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${AVCODEC_LIBRARY}
        ${AVFORMAT_LIBRARY}
        ${AVUTIL_LIBRARY}
        ${AVDEVICE_LIBRARY}
        ${SDL2TEST_LIBRARY}
        ${SDL2_LIBRARY}
        ${SDL2MAIN_LIBRARY}
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
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
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
