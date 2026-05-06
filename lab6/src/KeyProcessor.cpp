#include "KeyProcessor.hpp"
#include <iostream>

KeyProcessor::KeyProcessor() : curMode(ProcessMode::NORMAL) {}
void KeyProcessor::processKey(int key) {
    switch (key) {
        case '1': curMode = ProcessMode::NORMAL; break;
        case '2': curMode = ProcessMode::INVERT; break;
        case '3': curMode = ProcessMode::BLUR; break;
        case '4': curMode = ProcessMode::CANNY; break;
    }
}
ProcessMode KeyProcessor::getMode() const {
    return curMode;
}