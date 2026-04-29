#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class Display {
private:
    std::string windowName;

public:
    Display(const std::string& name = "Lab 6: OpenCV");
    bool isOpen() const; 

    void show(const cv::Mat& frame); 
    void setMouseCallback(cv::MouseCallback onMouse, void* userdata = nullptr); // Виправили велику B
    void addTrackbar(const std::string& trackbarName, int maxValue);
    int getTrackbarValue(const std::string& trackbarName) const;
};