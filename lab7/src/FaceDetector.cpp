#include "FaceDetector.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
using namespace dnn;

void FaceDetector::runAIInBackground(Mat frameCopy) {
    Mat blob = blobFromImage(frameCopy, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0));
    net.setInput(blob);
    Mat detections = net.forward();

    Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());
    vector<DetectResult> tempResults;

    for (int i = 0; i < detectionMat.rows; i++) {
        float confidence = detectionMat.at<float>(i, 2);
        if (confidence > 0.5) {
        
            int startX = static_cast<int>(detectionMat.at<float>(i, 3) * frameCopy.cols);
            int startY = static_cast<int>(detectionMat.at<float>(i, 4) * frameCopy.rows);
            int endX = static_cast<int>(detectionMat.at<float>(i, 5) * frameCopy.cols);
            int endY = static_cast<int>(detectionMat.at<float>(i, 6) * frameCopy.rows);
            
            tempResults.push_back({Rect(Point(startX, startY), Point(endX, endY)), confidence});
        }
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    mtx.lock();
    lastResults = tempResults;
    mtx.unlock();

    isAiRunning = false;
}
void FaceDetector::detectDNNsync(Mat& frame) {
    if (!isNetLoaded) {
        net = readNetFromCaffe("models/deploy.prototxt", "models/res10_300x300_ssd_iter_140000.caffemodel");
        isNetLoaded = true;
    }
    if (net.empty()) return;

    if (!isAiRunning) {
        isAiRunning = true;
        Mat frameCopy = frame.clone();
        thread t(&FaceDetector::runAIInBackground, this, frameCopy);
        t.detach(); 
    }

    mtx.lock();
    for (const auto& res : lastResults) {
        rectangle(frame, res.box, cv::Scalar(0, 255, 255), 2);
        string label = "Face: " + to_string((int)(res.confidence * 100)) + "%";
        putText(frame, label, Point(res.box.x, res.box.y - 10), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 255), 2);
    }
    mtx.unlock();
}