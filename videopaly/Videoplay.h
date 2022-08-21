//
// Created by admin on 2022/8/18.
//

#ifndef QT5DEMO_VIDEOPLAY_H
#define QT5DEMO_VIDEOPLAY_H

extern "C"
{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include<SDL.h>
}

class Videoplay {

private:
    //初始化SDL组件
    SDL_Rect rect;                              //渲染显示面积
    SDL_Window *window = NULL;                  // 窗口
    SDL_Renderer *renderer = NULL;              // 渲染
    SDL_Texture *texture = NULL;                // 纹理
    Uint32 pixformat;
public:
    ~ Videoplay();
    bool  initialization();
    void rendering(AVFrame *pFrame );
};


#endif //QT5DEMO_VIDEOPLAY_H
