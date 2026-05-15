#include "FaceDetector.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
using namespace dnn;

FaceDetector::FaceDetector(const string& prototxtPath, const string& modelPath) {
    net = readNetFromCaffe(prototxtPath, modelPath);
    if (net.empty()) {
        cerr << "Error: DNN model not found!" << endl;
    }
    workerThread = thread(&FaceDetector::runAIInBackground, this);
}
FaceDetector::~FaceDetector() {
    isRunning = false;
    cv.notify_all();
    if (workerThread.joinable()) {
        workerThread.join();
    }
}
void FaceDetector::updateFrame(const Mat& frame) {
    lock_guard<mutex> lock(mtx);
    if (!hasNewFrame) {
        currentFrame = frame.clone();
        hasNewFrame = true;
        cv.notify_one();
    }
}
vector<DetectResult> FaceDetector::getResults() {
    lock_guard<mutex> lock(mtx);
    return lastResults;
}
void FaceDetector::runAIInBackground() {
    while(isRunning) {
        Mat frameForAI;
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { return hasNewFrame || !isRunning; });
            
            if (!isRunning) break;
            
            frameForAI = currentFrame.clone();
            hasNewFrame = false;
        }
        if (frameForAI.empty() || net.empty()) continue;

        Mat blob = blobFromImage(frameForAI, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0));
        net.setInput(blob);
        Mat detections = net.forward();
        Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());
        vector<DetectResult> tempResults;

        for (int i = 0; i < detectionMat.rows; i++) {
            float confidence = detectionMat.at<float>(i, 2);
            if (confidence > 0.5) {
                int startX = static_cast<int>(detectionMat.at<float>(i, 3) * frameForAI.cols);
                int startY = static_cast<int>(detectionMat.at<float>(i, 4) * frameForAI.rows);
                int endX = static_cast<int>(detectionMat.at<float>(i, 5) * frameForAI.cols);
                int endY = static_cast<int>(detectionMat.at<float>(i, 6) * frameForAI.rows);
                
                tempResults.push_back({Rect(Point(startX, startY), Point(endX, endY)), confidence});
            }
        }

        this_thread::sleep_for(chrono::milliseconds(500));

        {
            lock_guard<mutex> lock(mtx);
            lastResults = tempResults;
        }
    }
}