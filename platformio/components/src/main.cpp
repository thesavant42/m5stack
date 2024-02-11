#include <M5Unified.h>
#include <M5GFX.h>

#include "features/display.h"
#include "features/scheduler.h"

M5GFX display;
Scheduler scheduler;

void setup() {
  initDisplay(display);

  display.setFont(&fonts::efontJA_16);
  display.println("こんにちは日本");



  
}

void loop() {
  display.waitDisplay();

  if (scheduler.intervalMs(100)) {
    // autoBrightness();
  }

  display.display();
}
