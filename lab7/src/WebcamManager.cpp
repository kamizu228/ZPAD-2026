#include "WebcamManager.hpp"
#include <iostream>

using namespace cv;
using namespace std;

WebcamManager::WebcamManager(int cameraId) {
    cap.open(cameraId);

    if (!cap.isOpened()) {
        cerr << "Error: camare not found!" << endl;
    }
    else {
        cap.set(CAP_PROP_FRAME_WIDTH, 1280);
        cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    }
}
WebcamManager::~WebcamManager() {
    if (cap.isOpened()) {
        cap.release();
    }
}

bool WebcamManager::isReady() const {
    return cap.isOpened();
}

Mat WebcamManager::getFrame() {
    Mat frame;
    cap >> frame;
    return frame;
}

