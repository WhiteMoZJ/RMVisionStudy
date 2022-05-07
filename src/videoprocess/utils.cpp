#include "utils.h"

/*
* @brief	图像属性调节装置
*/
void Utils::trackBar()
{
	//cv::namedWindow("Origin", cv::WINDOW_NORMAL);
	//cv::namedWindow("Test", cv::WINDOW_NORMAL); 
	cv::namedWindow("Settings", cv::WINDOW_NORMAL);
	cv::createTrackbar("Tresh", "Settings", &tresh, tresh_max, 0, 0);		//调节二值化阈值
	cv::createTrackbar("KernelSize", "Settings", &size, size_max, 0, 0);	//调节卷积核大小
    cv::createTrackbar("Bright", "Settings", &alpha, alpha_max, 0, 0);		//调节亮度
}

/*
* @brief	装甲板框选
* @param cv::Mat pic			画直线的图像
* @param cv::Point2f locs[]		坐标点的集合
*/
void Utils::drawRect(cv::Mat& pic, cv::Point2f locs[])
{
    for (int i = 0; i < 4; i++) {
        if (i == 3) {
            cv::line(pic, locs[i], locs[0], cv::Scalar(0, 255, 200), 3, 8, 0);
            break;
        }
        cv::line(pic, locs[i], locs[i + 1], cv::Scalar(0, 255, 200), 3, 8, 0);
    }
}


/*
* @brief	画点
* @param cv::Mat pic				画点的图像
* @param cv::Point2d point			所画点的坐标
* @param const cv::String &text		标记字符
*/
void Utils::drawPoint(cv::Mat& pic, cv::Point2d& point, const cv::String& text)
{
	cv::putText(pic, text, point, 0, 1, cv::Scalar(255, 255, 255), 2);
	cv::circle(pic, point, 4, cv::Scalar(255, 0, 255), -1, 8);
    cv::putText(pic, "X " + std::to_string(point.x), cv::Point(point.x, point.y + 20),
		cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1, 8);
    cv::putText(pic, "Y " + std::to_string(point.y), cv::Point(point.x, point.y + 37),
		cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1, 8);  //显示坐标//显示坐标
}

/*
* @brief	画圆
* @param cv::Mat pic			画圆的图像
* @param cv::Point2d point		拟合圆用坐标
*/
void Utils::drawFittingCircle(cv::Mat& pic, cv::Point2d& point)
{
	circle_points.push_back(point);
	if (circle_points.size() > 75) {
		auto p = circle_points.begin();
		circle_points.erase(p);
	}
	leastSquaresCircleFitting(center, radius);						//拟合圆
	cv::circle(pic, center, cvRound(radius), cv::Scalar(255, 255, 255), 1, 8);	//绘制拟合圆
	drawPoint(pic, center, "Center");			//绘制圆心
	//std::cout << "Center" << center << std::endl;
	//std::cout << "Radius" << radius << std::endl;
}


/*
* @brief	最小二乘法拟合圆
* @param cv::Point2d & center					圆心
* @param double& radius							圆半径
*/

int Utils::leastSquaresCircleFitting(cv::Point2d& center, double& radius)
{
	if (!circle_points.empty()) {
		int iNum = (int)circle_points.size();
		if (iNum < 3) {
			return 1;
		}
		double X1 = 0.0;
		double Y1 = 0.0;
		double X2 = 0.0;
		double Y2 = 0.0;
		double X3 = 0.0;
		double Y3 = 0.0;
		double X1Y1 = 0.0;
		double X1Y2 = 0.0;
		double X2Y1 = 0.0;
		std::vector<cv::Point2d>::iterator iter;
		auto end = circle_points.end();
		for (iter = circle_points.begin(); iter != end; ++iter) {
			X1 = X1 + (*iter).x;
			Y1 = Y1 + (*iter).y;
			X2 = X2 + (*iter).x * (*iter).x;
			Y2 = Y2 + (*iter).y * (*iter).y;
			X3 = X3 + (*iter).x * (*iter).x * (*iter).x;
			Y3 = Y3 + (*iter).y * (*iter).y * (*iter).y;
			X1Y1 = X1Y1 + (*iter).x * (*iter).y;
			X1Y2 = X1Y2 + (*iter).x * (*iter).y * (*iter).y;
			X2Y1 = X2Y1 + (*iter).x * (*iter).x * (*iter).y;
		}
		double C = 0.0;
		double D = 0.0;
		double E = 0.0;
		double G = 0.0;
		double H = 0.0;
		double a = 0.0;
		double b = 0.0;
		double c = 0.0;
		C = iNum * X2 - X1 * X1;
		D = iNum * X1Y1 - X1 * Y1;
		E = iNum * X3 + iNum * X1Y2 - (X2 + Y2) * X1;
		G = iNum * Y2 - Y1 * Y1;
		H = iNum * X2Y1 + iNum * Y3 - (X2 + Y2) * Y1;
		a = (H * D - E * G) / (C * G - D * D);
		b = (H * C - E * D) / (D * D - G * C);
		c = -(a * X1 + b * Y1 + X2 + Y2) / iNum;
		double A = 0.0;
		double B = 0.0;
		double R = 0.0;
		A = a / (-2);
		B = b / (-2);
		R = double(sqrt(a * a + b * b - 4 * c) / 2);
		center.x = A;
		center.y = B;
		radius = R;
		return 0;
	}
	else
		return 1;
	return 0;
}
