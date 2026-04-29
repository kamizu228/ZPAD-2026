#include "MouseProcessor.hpp"

MouseProcessor::MouseProcessor() : isDrawing(false), zoomFactor(1.0) {}
void MouseProcessor::mouseCallback(int event, int x, int y, int flags, void* userdata) {
    MouseProcessor* processor = static_cast<MouseProcessor*>(userdata);
    if (processor) {
        processor->handleEvent(event, x, y, flags);
    }
}

void MouseProcessor::handleEvent(int event, int x, int y, int flags) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        isDrawing = true;
        pt1 = cv::Point(x, y);
        pt2 = pt1; // Початкова точка
    } 
    else if (event == cv::EVENT_MOUSEMOVE && isDrawing) {
        pt2 = cv::Point(x, y); // Оновлюємо координати під час перетягування
    } 
    else if (event == cv::EVENT_LBUTTONUP) {
        isDrawing = false;
        pt2 = cv::Point(x, y);
        // Зберігаємо готовий прямокутник у пам'ять
        rectangles.push_back(cv::Rect(pt1, pt2));
    }
    else if (event == cv::EVENT_RBUTTONDOWN) {
        // На праву кнопку очищаємо всі малюнки
        rectangles.clear();
    }
    else if (event == cv::EVENT_MOUSEWHEEL) {
        int delta = cv::getMouseWheelDelta(flags);
        if (delta > 0) {
            zoomFactor = zoomFactor * 1.1;
        }
        else {
            zoomFactor = zoomFactor / 1.1;
        }

        if (zoomFactor < 1.0) zoomFactor = 1.0;
        else if (zoomFactor > 10.0) zoomFactor = 10.0;
    }
}

void MouseProcessor::drawOn(cv::Mat& frame) {
    // Малюємо всі збережені прямокутники (зеленим)
    for (const auto& rect : rectangles) {
        cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
    }
    // Малюємо той, який зараз тягнемо (червоним)
    if (isDrawing) {
        cv::rectangle(frame, cv::Rect(pt1, pt2), cv::Scalar(0, 0, 255), 2);
    }
    if (zoomFactor > 1.0) {
        int W = frame.cols;
        int H = frame.rows;

        int newW = W / zoomFactor;
        int newH = H / zoomFactor;

        int x = (W - newW) / 2;
        int y = (H - newH) / 2;

        cv::Rect roi(x, y, newW, newH); // Створюємо прямокутник для вирізання
        cv::Mat crop = frame(roi); // Вирізаємо суб-матрицю
        cv::Mat resultCrop;
        resultCrop = crop.clone();
        cv::resize(resultCrop, frame, cv::Size(W, H)); // Розтягуємо назад до оригінального розміру
    }
}