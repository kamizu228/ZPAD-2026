#include "Display.hpp"

using namespace cv;
using namespace std;

Display::Display(const string& name) : windowName(name) {
    namedWindow(windowName, cv::WINDOW_NORMAL);
    resizeWindow(windowName, 1280, 720);
}
bool Display::isOpen() const {
    return getWindowProperty(windowName, WND_PROP_VISIBLE) >= 1;
}
void Display::show(const cv::Mat& frame) {
    if(!frame.empty()) {
        imshow(windowName, frame);
    }
}
