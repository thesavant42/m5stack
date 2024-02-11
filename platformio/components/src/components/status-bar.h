#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../const.h"
#include "battery.h"
#include "wifi-status.h"

extern M5GFX display;

void drawStatusBar() {
  display.fillRect(0, 0, display.width(), 20, BLACK_COLOR);

  drawBattery(display.width() - 30, 4);
  drawWifiStatus(display.width() - 55, 2);
};

#endif
