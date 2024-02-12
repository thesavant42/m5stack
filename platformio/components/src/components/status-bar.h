#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../const.h"
#include "battery.h"
#include "clock.h"
#include "wifi-status.h"

extern M5GFX display;

void drawStatusBar() {
  LGFX_Sprite statusBar;

  statusBar.createSprite(display.width(), 26);
  statusBar.fillScreen(BLACK_COLOR);

  drawClock(&statusBar, 4, 5);
  drawWifiStatus(&statusBar, statusBar.width() - 65, 5);
  drawBattery(&statusBar, statusBar.width() - 35, 6);

  statusBar.pushSprite(&display, 0, 0);
  statusBar.deleteSprite();
};

#endif
