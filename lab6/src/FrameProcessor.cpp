#include "FrameProcessor.hpp"

cv::Mat FrameProcessor::process(const cv::Mat& inputFrame, ProcessMode mode) {
    cv::Mat resultFrame;

    switch (mode) {
        case ProcessMode::NORMAL:
            resultFrame = inputFrame.clone();
            break;

        case ProcessMode::INVERT:
            cv::bitwise_not(inputFrame, resultFrame);
            break;

        case ProcessMode::BLUR:
            cv::GaussianBlur(inputFrame, resultFrame, cv::Size(15, 15), 0);
            break;

        case ProcessMode::CANNY:
            cv::Mat tempFrame;
            cv::cvtColor(inputFrame, tempFrame, cv::COLOR_BGR2GRAY);
            cv::Canny(tempFrame, resultFrame, 50, 150);
            break;
    }
    return resultFrame;
}