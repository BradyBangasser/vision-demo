#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <vision/VisionPipeline.h>

class BVPipeline : public frc::VisionPipeline {
    protected:
        int val = 0;
    public:
        void Process(cv::Mat &mat) override;
};

#endif