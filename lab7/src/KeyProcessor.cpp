#include "KeyProcessor.hpp"

KeyProcessor::KeyProcessor() : curMode(ProcessMode::NORMAL) {}
void KeyProcessor::processKey(int key) {
    switch (key) {
        case '1': 
            curMode = ProcessMode::NORMAL; 
            break;
        case 'f': 
        case 'F': 
            curMode = ProcessMode::FACE_DETECTION; 
            break;
    }
}
ProcessMode KeyProcessor::getMode() const {
    return curMode;
}