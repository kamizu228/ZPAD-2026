#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <string>

    struct DetectResult {
        cv::Rect box;
        float confidence;
    };

class FaceDetector {
private:
    cv::dnn::Net net;
    std::mutex mtx;
    std::thread workerThread;
    std::condition_variable cv;

    std::atomic<bool> isRunning{true};
    bool hasNewFrame = false;
    cv::Mat currentFrame;

    std::vector<DetectResult> lastResults;
    void runAIInBackground();
public:
    FaceDetector(const std::string& prototxtPath, const std::string& modelPath);
    ~FaceDetector();
    void updateFrame(const cv::Mat& frame);
    std::vector<DetectResult> getResults();
};