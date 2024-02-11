#ifndef BATTERY_H
#define BATTERY_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../const.h"

extern M5GFX display;

void drawBattery(LGFX_Sprite* sprite, int x, int y) {
  int width = 25;
  int height = 13;
  int32_t level = M5.Power.getBatteryLevel();

  // バッテリーの枠をスプライトに描画
  sprite->drawRect(x, y, width, height, WHITE_COLOR);

  // バッテリーの頭部をスプライトに描画
  int headWidth = 3;
  sprite->fillRect(x + width, y + height / 4, headWidth, height / 2,
                   WHITE_COLOR);

  // バッテリーレベルに基づいて内部をスプライトに塗りつぶす
  int fillWidth = (level * (width - 2)) / 100;
  sprite->fillRect(x + 1, y + 1, fillWidth, height - 2, WHITE_COLOR);
}

#endif
