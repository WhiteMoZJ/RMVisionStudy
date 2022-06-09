#include "video_process.h"
#include <ctime>
#include <string>

/*
* @brief	图像缓存
*/
void VideoProcess::getVideo()
{
	//！这里设置了重复播放
    // Warning: endless loop
	while (true)
	{
		cv::VideoCapture video(video_add);
		//cv::VideoCapture video(cam_add);
		while (true)
		{
			clock_t time_start = clock();
			video >> pic;
			pic.copyTo(pic_pro);	//复制一份图像
			if (pic.empty()) {
				break;
			}
			processVideo();
			BD.buffDetect(pic, pic_pro);
			clock_t time_end = clock();
			//std::cout << "time use: " << time << "ms" << std::endl;		//计时
            cv::putText(pic, "TIME USED PER FRAME: " + std::to_string((int)(1000.0 * (time_end - time_start) / (double)CLOCKS_PER_SEC)) + " ms", cv::Point(10, 20),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
            cv::putText(pic, "VIDEO/CAM FPS: " + std::to_string((int)video.get(cv::CAP_PROP_FPS)) + " FPS", cv::Point(10, 35), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
            cv::putText(pic, "CAP FPS:       " + std::to_string((int)(1/((time_end - time_start) / (double)CLOCKS_PER_SEC))) + " FPS", cv::Point(10, 50),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
			cv::putText(pic, "VIDEO WIDTH:  " + std::to_string((int)video.get(cv::CAP_PROP_FRAME_WIDTH)) + " p", cv::Point(10, 65), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
			cv::putText(pic, "VIDEO HEIGHT: " + std::to_string((int)video.get(cv::CAP_PROP_FRAME_HEIGHT)) + " p", cv::Point(10, 80), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
            cv::imshow("Origin", pic);
            cv::imshow("Test", pic_pro);
			cv::waitKey(1);
		}
		cv::waitKey(1);
	}
}

/*
* @brief	图像处理
* 
*/
void VideoProcess::processVideo()
{
    pic = ST.adjustBright(pic);
    cv::Size kernel_size = cv::Size(ST.utils.size, ST.utils.size);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, kernel_size);	//图像处理用卷积核
	//setExposure();
	cvtColor(pic_pro, pic_pro, cv::COLOR_BGR2GRAY);								//转灰度图
    cv::threshold(pic_pro, pic_pro, ST.utils.tresh, 255, cv::THRESH_BINARY);	//二值化
	cv::dilate(pic_pro, pic_pro, kernel);										//膨胀
	cv::morphologyEx(pic_pro, pic_pro, cv::MORPH_CLOSE, kernel);				//闭运算
    //略微提高识别精准度 但对运算速度影响较大 ~5ms 但相对轮廓关系会发生改变
	//cv::Canny(pic_pro, pic_pro, 5, 200);
}
