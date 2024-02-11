#ifndef BATTERY_H
#define BATTERY_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../const.h"

extern M5GFX display;

void drawBattery(int x, int y) {
  int width = 30;
  int height = 15;
  int32_t level = M5.Power.getBatteryLevel();

  // バッテリーの枠を描画
  display.drawRect(x, y, width, height, WHITE_COLOR);

  // バッテリーの頭部を描画
  int headWidth = 3;
  display.fillRect(x + width, y + height / 4, headWidth, height / 2,
                   WHITE_COLOR);

  // バッテリーレベルに基づいて内部を塗りつぶす
  int fillWidth = (level * (width - 2)) / 100;
  display.fillRect(x + 1, y + 1, fillWidth, height - 2, GREEN_COLOR);
}

#endif
