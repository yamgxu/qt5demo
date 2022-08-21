//
// Created by admin on 2022/8/18.
//
#include <QGuiApplication>

#include "Videoplay.h"

bool Videoplay::initialization() {

    //视频分辨率
    int w_width = 1920;
    int w_height = 1080;

    //SDL初始化
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        qDebug("can not initialize SDL");
        return false;
    }
    //SDL 窗口初始化
    window = SDL_CreateWindow("MEDIA PLAYER",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              w_width, w_height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        qDebug("can not create window");
        return false;
    }
    //SDL 渲染器初始化
    renderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        qDebug("can not create renderer!");
        return false;
    }
    //SDL 视频格式与纹理初始化
    pixformat = SDL_PIXELFORMAT_IYUV;
    texture = SDL_CreateTexture(renderer,
                                pixformat,
                                SDL_TEXTUREACCESS_STREAMING,
                                w_width,
                                w_height);

    // Enter full screen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    return true;

}

Videoplay::~Videoplay() {

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}


void Videoplay::rendering(AVFrame *pFrame) {
    //SDL 刷新纹理
    SDL_UpdateYUVTexture(texture, nullptr,
                         pFrame->data[0], pFrame->linesize[0],
                         pFrame->data[1], pFrame->linesize[1],
                         pFrame->data[2], pFrame->linesize[2]);
    rect.x = 0;//SDL设置渲染目标的显示区域
    rect.y = 0;
    rect.w = pFrame->width;
    rect.h = pFrame->height;

    SDL_RenderClear(renderer);//SDL 清空渲染器内容
    SDL_RenderCopy(renderer, texture, nullptr, &rect);//SDL 将纹理复制到渲染器
    SDL_RenderPresent(renderer);//SDL 渲染



}


