#include "setting.h"


/*
* @brief	设置亮度
* @param	cv::Mat src		图像
* @return	cv::Mat dst_BR	调节后的图像
*/
cv::Mat Setting::adjustBright(const cv::Mat& src)
{
	cv::Mat dst_BR = cv::Mat::zeros(src.size(), src.type());
	cv::Mat BrightnessLut(1, 256, CV_8UC1);
	for (int i = 0; i < 256; i++) {
		BrightnessLut.at<uchar>(i) = cv::saturate_cast<uchar>(i + utils.alpha - 50);
	}
	cv::LUT(src, BrightnessLut, dst_BR);
	return dst_BR;
}
