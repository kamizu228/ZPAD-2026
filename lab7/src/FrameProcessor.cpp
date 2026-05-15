#include "FrameProcessor.hpp"

using namespace cv;
using namespace std;

FrameProcessor::FrameProcessor()
    : faceDetector("models/deploy.prototxt", "models/res10_300x300_ssd_iter_140000.caffemodel") {}

Mat FrameProcessor::process(const Mat& inputFrame, ProcessMode mode) {
    Mat resultFrame = inputFrame.clone();

    switch (mode) {
        case ProcessMode::NORMAL:
            break;
        case ProcessMode::FACE_DETECTION:
            faceDetector.updateFrame(resultFrame);
            
            auto results = faceDetector.getResults();

            for (const auto& res : results) {
                rectangle(resultFrame, res.box, cv::Scalar(0, 255, 255), 2);
                string label = "Face: " + to_string((int)(res.confidence * 100)) + "%";
                putText(resultFrame, label, Point(res.box.x, res.box.y - 10), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 255), 2);
            }
            break;
    }
    return resultFrame;
}