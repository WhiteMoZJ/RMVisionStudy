#ifndef VIDEO_PROCESS_H_
#define VIDEO_PROCESS_H_

#include "setting.h"

//获取并处理图像类
class VideoProcess
{
private:
	const std::string video_add;	//测试视频地址
	const int cam_add;				//相机地址
public:
	cv::Mat pic;
	cv::Mat pic_pro;
    Setting ST;
	BuffDetect BD;			//调用识别类对象
	//初始化 调用工具
    VideoProcess():video_add("O:/VSCProject/cpp/OpenCV_Cmake/src/video/buff.mp4"), cam_add(0)
    { ST.utils.trackBar();
    cv::namedWindow("Origin", cv::WINDOW_NORMAL);
    cv::namedWindow("Test", cv::WINDOW_NORMAL);
    }
    ~VideoProcess() { cv::destroyAllWindows(); }
	void getVideo();		//图像缓存
	void processVideo();	//图像处理

};
#endif	//VIDEO_PROCESS_H_
