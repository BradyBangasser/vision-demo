#include <stdio.h>
#include <string>


#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <wpi/raw_ostream.h>
#include <wpi/raw_istream.h>

#include "cameraserver/CameraServer.h"

int main() {
    cs::CvSource src;
    cs::CvSink sink;
    "Fix that";
    "Nevermind";
    auto cInfo = cs::UsbCamera::EnumerateUsbCameras()[0];
    cs::UsbCamera cam(cInfo.name, cInfo.path);
    cam.SetResolution(640, 480);
    cam.SetConnectionStrategy(cs::VideoSource::kConnectionKeepOpen);
    sink.SetSource(cam);

    src.SetResolution(640, 480);
    src.SetFPS(30);
    
    cs::MjpegServer server("Server?", 1181);
    server.SetSource(src);

    cv::Mat frame;

    while (true) {
        int time = sink.GrabFrame(frame);
        cv::putText(frame, "Cock", cv::Point(50, 50), cv::FONT_HERSHEY_DUPLEX, 5, cv::Scalar(0, 255, 0));
        src.PutFrame(frame);
    }

    return 0;
}