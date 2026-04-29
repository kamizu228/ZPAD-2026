#pragma once

enum class ProcessMode {
    NORMAL,
    INVERT,
    BLUR,
    CANNY
};

class KeyProcessor {
private:
    ProcessMode curMode;
public:
    KeyProcessor();

    void processKey(int key);
    ProcessMode getMode() const;
};