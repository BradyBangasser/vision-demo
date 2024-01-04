#include "pipeline.hpp"
#include <fmt/format.h>
#include <opencv2/imgproc.hpp>

void BVPipeline::Process(cv::Mat &mat) {
    ++val;

    throw ("COCKS");
    cv::rectangle(mat, cv::Rect(cv::Point2d(0, 0), cv::Point2d(500, 500)), cv::Scalar(255, 255, 255));
}