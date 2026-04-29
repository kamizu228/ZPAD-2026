#include "../include/Display.hpp"

Display::Display(const std::string& name) : windowName(name) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::resizeWindow(windowName, 1280, 720);
}
bool Display::isOpen() const {
    return cv::getWindowProperty(windowName, cv::WND_PROP_VISIBLE) >= 1;
}
void Display::show(const cv::Mat& frame) {
    if(!frame.empty()) {
        cv::imshow(windowName, frame);
    }
}
void Display::setMouseCallback(cv::MouseCallback onMouse, void* userdata) {
    cv::setMouseCallback(windowName, onMouse, userdata);
}
void Display::addTrackbar(const std::string& trackbarName, int maxValue) {
    cv::createTrackbar(trackbarName, windowName, nullptr, maxValue);
}
int Display::getTrackbarValue(const std::string& trackbarName) const {
    return cv::getTrackbarPos(trackbarName, windowName);
}