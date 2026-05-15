#pragma once
#include <opencv2/opencv.hpp>

class WebcamManager {
private:
    cv::VideoCapture cap;
public:
    WebcamManager(int cameraId);
    ~WebcamManager();

    bool isReady() const;
    cv::Mat getFrame();
};
