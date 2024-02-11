#include <M5GFX.h>
#include <M5Unified.h>

#include "features/brightness.h"
#include "features/display.h"
#include "features/font.h"
#include "features/scheduler.h"

M5GFX display;
Scheduler scheduler;

void setup() {
  M5.begin();

  initDisplay();
  initAutoBrightness();
  initFont();

  p("こんにちは日本");
}

void loop() {
  M5.update();

  display.waitDisplay();

  if (scheduler.intervalMs(1000)) {
    autoBrightness();
  }

  display.display();
}
