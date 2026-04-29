#include "../include/CameraProvider.hpp"
#include <iostream>

CameraProvider::CameraProvider(int camId) {
    cap.open(camId);

    if (!cap.isOpened()) {
        std::cerr << "Помилка: не вдалося відкрити камеру!" << std::endl;
    }
    else {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    }
}
CameraProvider::~CameraProvider() {
    if (cap.isOpened()) {
        cap.release();
    }
}

bool CameraProvider::isOpened() const {
    return cap.isOpened();
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;
    cap >> frame;
    return frame;
}