#include "WebcamManager.hpp"
#include "Display.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    WebcamManager camera(0);
    Display display("Lab 7");
    KeyProcessor keyProcessor;
    FrameProcessor frameProcessor;

    if (!camera.isReady()) {
        return -1;
    }

    int64 timer = getTickCount();

    while (true) {
        Mat frame = camera.getFrame();
        if (frame.empty()) {
            cerr << "Frame not found or camera is turned off!" << endl;
            break;
        }
        if (!display.isOpen()) {
            std::cout << "The window was closed by the user." << std::endl;
            break;
        }

        Mat processFrame = frameProcessor.process(frame, keyProcessor.getMode());

        double fps = getTickFrequency() / (getTickCount() - timer);
        string fpsText = "FPS: " + to_string((int)fps);
        putText(processFrame, fpsText, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 0), 2);
        timer = getTickCount();

        display.show(processFrame);

        int key = waitKey(1);

        if (key == 27 || key == 'q') {
            break;
        }
        if (key != -1) {
            keyProcessor.processKey(key);
        }
    }
    return 0;
}