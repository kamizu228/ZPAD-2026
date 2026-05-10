#include "FrameProcessor.hpp"

using namespace cv;

Mat FrameProcessor::process(const Mat& inputFrame, ProcessMode mode) {
    Mat resultFrame = inputFrame.clone();

    switch (mode) {
        case ProcessMode::NORMAL:
            break;
        case ProcessMode::FACE_DETECTION:
            faceDetector.detectDNNsync(resultFrame);
            break;
    }
    return resultFrame;
}