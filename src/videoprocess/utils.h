#ifndef UTILS_H_
#define UTILS_H_

#include <opencv2/opencv.hpp>

//DEBUG调试工具类
class Utils
{
private:
	const int size_max;		//卷积核最大尺寸
	const int tresh_max;	//最大阈值
    const int alpha_max;	//曝光最大值

public:
	int size;	//卷积核大小
	int tresh;	//阈值
    int alpha;
	std::vector<cv::Point2d> circle_points;	//拟合圆点集
	cv::Point2d center;						//拟合圆圆心
	double radius;							//拟合圆半径
	
    Utils() :size_max(21), tresh_max(255), alpha_max(100),
        size(3), tresh(120), alpha(30) {
		radius = 0;
	}
	~Utils(){ std::vector<cv::Point2d>().swap(circle_points); }
	void trackBar();
	static void drawRect(cv::Mat& pic, cv::Point2f locs[]);
	static void drawPoint(cv::Mat& pic, cv::Point2d& point, const cv::String& text);
	void drawFittingCircle(cv::Mat& pic, cv::Point2d& point);
	int leastSquaresCircleFitting(cv::Point2d& center, double& radius);
};

#endif //UTILS_H_
