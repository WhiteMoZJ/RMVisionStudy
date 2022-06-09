#ifndef SETTING_H_
#define SETTING_H_

#include "../buff_detect.h"

class Setting
{

public:
	Setting() = default;
	Utils utils;

	cv::Mat adjustBright(const cv::Mat& src);	//调节亮度，画面亮度非获取亮度
};

#endif // SETTING_H_
