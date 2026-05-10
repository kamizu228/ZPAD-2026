// Винести детекцію обличчя в окремий потік, щоб відео залишалось ідеально плавним (30-60 FPS), а рамка оновлювалась асинхронно.
#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <string>

class FaceDetector {
private:
    cv::dnn::Net net;
    bool isNetLoaded = false;
    std::atomic<bool> isAiRunning{false};
    std::mutex mtx;

    struct DetectResult {
        cv::Rect box;
        float confidence;
    };
    std::vector<DetectResult> lastResults;
    void runAIInBackground(cv::Mat frameCopy);
public:
    void detectDNNsync(cv::Mat& frame);
};