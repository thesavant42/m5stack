#include <M5GFX.h>
#include <M5Unified.h>

#include "features/brightness.h"
#include "features/display.h"
#include "features/scheduler.h"

M5GFX display;
Scheduler scheduler;

void setup() {
  M5.begin();

  initDisplay(&display);
  initAutoBrightness();

  display.setFont(&fonts::efontJA_16);
  display.println("こんにちは日本");
}

void loop() {
  M5.update();

  display.waitDisplay();

  if (scheduler.intervalMs(100)) {
    autoBrightness();
  }

  display.display();
}
