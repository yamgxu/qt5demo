//
// Created by admin on 2022/8/18.
//

#include "Decoder.h"

/*Decoder::initialization() {

}*/

 bool Decoder::playVideoFile(const char *file) {

    //FFMPEG 视频文件读取
    if (avformat_open_input(&pFormatCtx, file, nullptr, nullptr) != 0) {
        qDebug("can not open the video file");
        return false;
    }

    //FFMPEG 寻找视频流
    videoStreamMarked = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (videoStreamMarked == -1) {
        qDebug("can not open a video stream");
        return false;

    }

    //FFMPEG 寻找合适的解码器
    pCodeParameters = pFormatCtx->streams[videoStreamMarked]->codecpar;
    pCodec = avcodec_find_decoder(pCodeParameters->codec_id);
    if (pCodec == nullptr) {
        qDebug("can not find a codec");
        return false;

    }

    //FFMPEG 解码器信息配置
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (avcodec_parameters_to_context(pCodecCtx, pCodeParameters) != 0) {
        qDebug("can not copy codec context");
        return false;

    }

    //FFMPEG 解码器启动
    if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0) {
        qDebug(" can not open the Decoder");
        return false;

    }


    return true;

}

Decoder::~Decoder() {
    if (pFrame) {
        av_frame_free(&pFrame);
        pFrame = nullptr;
    }
    if (pCodecCtx) {
        avcodec_close(pCodecCtx);
        pCodecCtx = nullptr;
        pCodec = nullptr;
    }
    if (pCodeParameters) {
        avcodec_parameters_free(&pCodeParameters);
        pCodeParameters = nullptr;
    }
    if (pFormatCtx) {
        avformat_close_input(&pFormatCtx);
    }

    if (pFormatCtx) {
        avformat_free_context(pFormatCtx);
        pFormatCtx = nullptr;
    }
}


bool Decoder::send_packet() {

    while (av_read_frame(pFormatCtx,&packet)>= 0) {//FFMPEG 如果已经读到了一个帧
        if (packet.stream_index == videoStreamMarked) {//并且该帧是视频帧
            avcodec_send_packet(pCodecCtx,&packet);
            av_packet_unref(&packet);
            return true;
        }
        av_packet_unref(&packet);
    }

    return false;
}

int Decoder::receive_frame(AVFrame *pAvFrame) {
    return avcodec_receive_frame(pCodecCtx, pAvFrame);
}
