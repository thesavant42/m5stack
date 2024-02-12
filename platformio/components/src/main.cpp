#include <M5GFX.h>
#include <M5Unified.h>
#include <SD.h>

#include "apps/assistant.h"
#include "components/button.h"
#include "components/status-bar.h"
#include "const.h"
#include "features/brightness.h"
#include "features/display.h"
#include "features/env.h"
#include "features/rtc.h"
#include "features/scheduler.h"
#include "features/wifi.h"

Scheduler scheduler;
M5GFX display;

void setup() {
  M5.begin();

  // init
  initDisplay();
  initEnv(SD, "/env.txt");
  initWifi();
  initRtc();
  initAutoBrightness();

  // draw
  display.fillScreen(GRAY_COLOR);
  drawStatusBar();
  drawApp();
}

void loop() {
  M5.update();

  updateApp();

  if (scheduler.intervalMs(1000)) {
    autoBrightness();
  }

  if (scheduler.intervalMs(1000)) {
    drawStatusBar();
  }
}
