#pragma once
#include <opencv2/opencv.hpp>
#include "KeyProcessor.hpp"
#include "FaceDetector.hpp"

class FrameProcessor {
private:
    FaceDetector faceDetector;
public:
    FrameProcessor();
    cv::Mat process(const cv::Mat& inputFrame, ProcessMode mode);
};