#include <M5GFX.h>
#include <M5Unified.h>

#include "components/statusbar.h"
#include "const.h"
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

  drawStatusbar();
}

void loop() {
  M5.update();

  display.waitDisplay();

  if (scheduler.intervalMs(1000)) {
    autoBrightness();
  }

  if (scheduler.intervalMs(5000)) {
    drawStatusbar();
  }

  display.display();
}
