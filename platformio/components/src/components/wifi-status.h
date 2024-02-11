#ifndef WIFI_STATUS_H
#define WIFI_STATUS_H

#include <M5GFX.h>
#include <M5Unified.h>
#include <WiFi.h>

#include "../const.h"
#include "../features/font.h"

extern M5GFX display;

void drawWifiStatus(int x, int y) {
  int width = 3;            // 各バーの幅
  int height = 15;          // 最下部のバーの高さ
  int gap = 2;              // バー間の隙間
  int level = WiFi.RSSI();  // RSSI値を取得

  // RSSI値に基づいてバーの数を決定
  int bars = 0;
  if (level > -55)
    bars = 4;
  else if (level > -70)
    bars = 3;
  else if (level > -85)
    bars = 2;
  else if (level <= -85)
    bars = 1;

  for (int i = 0; i < 4; i++) {
    int barHeight = (i + 1) * (height / 4);  // 各バーの高さ
    int barY = y + (height - barHeight);  // Y位置を調整してバーを描画
    int color = (i < bars) ? WHITE_COLOR : GRAY_COLOR;
    display.fillRect(x + (i * (width + gap)), barY, width, barHeight, color);
  }
}

#endif
