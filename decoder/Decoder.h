//
// Created by admin on 2022/8/18.
//

#ifndef QT5DEMO_DECODER_H
#define QT5DEMO_DECODER_H
#include <QGuiApplication>
extern "C"
{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include<SDL.h>

}


class Decoder {
private:
    // 初始化ffmpeg组件
    AVFormatContext *pFormatCtx = nullptr;   //视频文件上下文
    int videoStreamMarked {};   //视频流标识
    AVCodecParameters *pCodeParameters = nullptr; //解码器相关参数
    const AVCodec *pCodec = nullptr;  //解码器
    AVCodecContext *pCodecCtx = nullptr;  // 解码器上下文
    AVPacket packet{}; // 解码前的帧
public:
    AVFrame *pFrame= nullptr;
    //bool  initialization();
    bool  send_packet();
    int   receive_frame(  AVFrame *pAvFrame );
    bool  playVideoFile(const char *file);
    ~Decoder();
};


#endif //QT5DEMO_DECODER_H
