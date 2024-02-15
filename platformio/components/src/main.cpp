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
m5::board_t board;

void setup() {
  M5.begin();
  board = M5.getBoard();

  // init
  initDisplay();
  initEnv(SD, "/env.txt");
  initWifi();
  initRtc();
  if (board == m5::board_t::board_M5StackCoreS3) {
    initAutoBrightness();
  }

  // draw
  display.fillScreen(GRAY_COLOR);
  drawStatusBar();
  drawApp();
}

void loop() {
  M5.update();

  updateApp();

  if (scheduler.intervalMs(1000)) {
    if (board == m5::board_t::board_M5StackCoreS3) {
      autoBrightness();
    }
  }

  if (scheduler.intervalMs(1000)) {
    drawStatusBar();
  }
}
