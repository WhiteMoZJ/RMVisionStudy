#include <opencv2/core/utils/logger.hpp>
#include "videoprocess/video_process.h"

int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    VideoProcess A;
    A.getVideo();
    cv::waitKey(1);
    return 0;
}
