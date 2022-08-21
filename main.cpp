#include <QGuiApplication>
#include <QThread>
#include <QDateTime>
#include "decoder/Decoder.h"
#include "videopaly/Videoplay.h"
#include <chrono>
#include <ctime>

using namespace std::chrono;
long long getMicroseconds() {
    system_clock::time_point time_point_now = system_clock::now(); // 获取当前时间点
    system_clock::duration duration_since_epoch = time_point_now.time_since_epoch(); // 从1970-01-01 00:00:00到当前时间点的时长
    time_t microseconds_since_epoch = duration_cast<microseconds>(duration_since_epoch).count(); // 将时长转换为微秒数
    time_t tm_microsec = microseconds_since_epoch ; // 当前时间的微妙数
    return tm_microsec;
}
int main(int argc, char *argv[]) {

    Decoder decoder;
    Videoplay videoplay;
    videoplay.initialization();
    decoder.playVideoFile("C:/Users/77039/Videos/2022-08-18 21-52-39.mkv");
    decoder.pFrame = av_frame_alloc();
    Uint32 frameStartTime=0;
    int frameNum=0;
    //% 1000000000
    while (decoder.send_packet()) {
        if (decoder.receive_frame(decoder.pFrame) == 0) {
            if(frameStartTime==0){
                frameStartTime = SDL_GetTicks();
            }
            frameNum++;
            videoplay.rendering(decoder.pFrame);
            Uint32 i = SDL_GetTicks();
            int delayTime =  (1000*frameNum/ 60)- (i - frameStartTime);
            if(delayTime>0){
                SDL_Delay(delayTime);
            }
        }
        SDL_Event event;// SDL事件
        SDL_PollEvent(&event);// 轮询事件
        switch (event.type) {
            case SDL_QUIT: //如果窗口被关闭
                return 0;
            default:
                break;
        }
    }




    return 0;


}

