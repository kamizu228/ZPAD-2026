#include "../include/CameraProvider.hpp"
#include "../include/KeyProcessor.hpp"
#include "../include/FrameProcessor.hpp"
#include "../include/Display.hpp"
#include "../include/MouseProcessor.hpp"
#include <iostream>

int main() {

    Display display("Lab 6");
    CameraProvider camera(0);
    KeyProcessor keyProcessor;
    FrameProcessor frameProcessor;
    MouseProcessor mouseProc;

    if (!camera.isOpened()) {
        return -1;
    }

    display.setMouseCallback(MouseProcessor::mouseCallback, &mouseProc);

    std::cout << "Програму запущено! Натискай 1, 2, 3, 4 для зміни режимів." << std::endl;
    std::cout << "Натисни 'q' або 'Esc' для виходу." << std::endl;

    display.addTrackbar("Brightness", 100);

    int64 timer = cv::getTickCount();

    while (true) {
        
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) {
            std::cout << "Камера відключилася або кадр порожній." << std::endl;
            break;
        }

        if (!display.isOpen()) {
            std::cout << "Вікно було закрито користувачем." << std::endl;
            break;
        }

        cv::Mat processedFrame = frameProcessor.process(frame, keyProcessor.getMode());
        
        int brightness = display.getTrackbarValue("Brightness");
        processedFrame = processedFrame + cv::Scalar(brightness, brightness, brightness);

        mouseProc.drawOn(processedFrame);
        
        double fps = cv::getTickFrequency() / (cv::getTickCount() - timer);
        std::string fpsText = "FPS: " + std::to_string((int)fps);
        cv::putText(processedFrame, fpsText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
        timer = cv::getTickCount();

        display.show(processedFrame);
        
        int key = cv::waitKey(30);
        
        if (key == 27 || key == 'q') {
            break; 
        }

        if (key != -1) {
            keyProcessor.processKey(key);
        }
    }

    return 0;
}