#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class MouseProcessor {
private:
    bool isDrawing;
    double zoomFactor;
    cv::Point pt1, pt2;
    std::vector<cv::Rect> rectangles;

public:
    MouseProcessor();
    static void mouseCallback(int event, int x, int y, int flags, void* userdata);
    void handleEvent(int event, int x, int y, int flags);
    void drawOn(cv::Mat& frame);
};