#pragma once

enum class ProcessMode {
    NORMAL,
    FACE_DETECTION
};

class KeyProcessor {
private:
    ProcessMode curMode;
public:
    KeyProcessor();

    void processKey(int key);
    ProcessMode getMode() const;
};