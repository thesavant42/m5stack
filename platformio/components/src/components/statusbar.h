#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../const.h"
#include "battery.h"

extern M5GFX display;

void drawStatusbar() {
  display.fillRect(0, 0, display.width(), 20, BLACK_COLOR);

  drawBattery(display.width() - 35, 2);
};

#endif
