#ifndef BUFF_DETECT_H_
#define BUFF_DETECT_H_

#include "videoprocess/utils.h"

//能量机关识别
class BuffDetect
{
private:
	cv::Point2f locs[4];
	cv::Point2d pt_cur;			//当前装甲板中心位置
	cv::Point2d pt_pre;			//预测装甲板位置
	std::vector<cv::Point2d> pts;
	std::vector<double> avg;	//简单滤波

    double area[500] = {0};
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	const double time_fps;	//帧间时间
public:
	Utils utils;
	BuffDetect() :time_fps(1.0 / 30) { }
	~BuffDetect(){
		std::vector<std::vector<cv::Point>>().swap(contours);
		std::vector<cv::Vec4i>().swap(hierarchy);
		std::vector<cv::Point2d>().swap(pts);
		std::vector<double>().swap(avg);
	}
	void buffDetect(cv::Mat& pic, cv::Mat& pic_pro);
	double angularVelocity();
	void angleTrans();
};

#endif //BUFF_DETECT_H_
