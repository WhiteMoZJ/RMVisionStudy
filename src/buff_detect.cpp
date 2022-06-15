#include "buff_detect.h"
#include <iostream>
#include <cmath>

/*
* @brief	能量机关装甲板识别
* @param cv::Mat pic			显示图像
* @param cv::Mat pic_pro		用于计算的图像
*/
void BuffDetect::buffDetect(cv::Mat& pic, cv::Mat& pic_pro)
{
	findContours(pic_pro, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);
    for (unsigned i = 0; i < hierarchy.size(); i++)
    {
        //std::cout << "Hierarchy" << hierarchy[i] << std::endl;
        //判断矩形序列
        area[i] = contourArea(contours[i]);
        if (area[i] > 5000 && hierarchy[i][0]==-1 && hierarchy[i][1]==-1) {
            //std::cout << "TargetHierarchy" << hierarchy[i] << std::endl;
            cv::RotatedRect rect = cv::minAreaRect(cv::Mat(contours[i]));	//最小外接矩形
            rect.points(locs);
            pt_cur = rect.center;
            Utils::drawRect(pic, locs);
            Utils::drawPoint(pic, pt_cur, "Target");     //增加约1~3ms
            utils.drawFittingCircle(pic, pt_cur);
            angularVelocity();
            angleTrans();       //后续加入滤波防抖
            Utils::drawRect(pic, locs);
            Utils::drawPoint(pic, pt_pre, "Predict");
            cv::line(pic, pt_cur, utils.center, cv::Scalar(0, 0, 255), 3);
            cv::line(pic, pt_pre, utils.center, cv::Scalar(0, 0, 255), 3);
        }
    }
}

/*
* @brief	    计算角速度
* @return double w.z     角速度
*/
double BuffDetect::angularVelocity()
{
    pts.emplace_back(pt_cur);
    std::vector<cv::Point2d>::iterator p;
    cv::Point2d vec;    //线速度（矢量）
    cv::Point2d r;      //半径向量
    cv::Point3d w;      //角速度向量
    if (pts.size() > 2) {
        p = pts.begin();
        vec = (pt_cur - *p)/time_fps;
        r = pt_cur - utils.center;
        w = { 0,0,vec.x * r.y - vec.y * r.x };  //线速度与半径向量的向量积即为角速度（弧度）
        pts.erase(p);
    }
    return w.z;
    //整个坐标默认为右手系，逆时针为正，顺时针为负
}

/*
* @brief	角度转换点
* @param cv::Point2d point			转换点
* @param cv::Point2d& center		圆心
* @param double& theta              转换角度
*/
cv::Point2d trans(cv::Point2d point, cv::Point2d& center, double& theta)
{
    cv::Mat R = (cv::Mat_<double>(2, 2) << std::cos(theta), -std::sin(theta),
                                                        std::sin(theta), std::cos(theta));
    cv::Mat vector_target = (cv::Mat_<double>(2, 1) << point.x - center.x,
                                                                    point.y - center.y);
    cv::Mat vector_predict = R * vector_target;
    cv::Point2d predict(vector_predict);
    return predict;
}

/*
* @brief	角度转换
*/
void BuffDetect::angleTrans()
{
    double w = -angularVelocity()/150000;   //由于angularVelocity()得出的角速度单位为像素，进行简单换算（角度）
    if (w > 0) std::cout << std::abs(w) << " counterclockwise\n";
    else std::cout << std::abs(w) << " clockwise\n";
    double sum = 0;
    if (std::abs(w) < 2) {
        avg.emplace_back(w);
    }
    if (avg.size() > 15) {
        auto p = avg.begin();   //后期由卡尔曼替代
        avg.erase(p);
    }
    for (double& i : avg) {
        sum += i;
    }
    w = sum / avg.size();
    std::cout << w << std::endl;
    double theta = w * 1;                   //规定时间转过的角度
    //std::cout << theta << std::endl;
    pt_pre = trans(pt_cur, utils.center, theta) + utils.center;
    for (auto & loc : locs) {
        loc = trans(loc, utils.center, theta) + utils.center;
    }
}
