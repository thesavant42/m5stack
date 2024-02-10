#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

class Scheduler {
private:
    unsigned long previousMillis = 0;

public:
    // 指定された間隔でtrueを返す関数
    bool execMs(unsigned long interval) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            return true;
        }
        return false;
    }
};

#endif // SCHEDULER_H
