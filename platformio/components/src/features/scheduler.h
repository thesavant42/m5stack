#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

class Scheduler {
 private:
  unsigned long previousMillis = 0;

 public:
  bool intervalMs(unsigned long interval) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      return true;
    }
    return false;
  }
};

#endif
