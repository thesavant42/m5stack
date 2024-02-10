#ifndef BATTERY_H
#define BATTERY_H

#include <M5Unified.h>

void drawBattery() {
  int x = 275;
  int y = 0;
  int width = 35;
  int height = 15;
  int32_t level = M5.Power.getBatteryLevel();

  // バッテリーの枠を描画
  M5.Lcd.drawRect(x, y, width, height, WHITE);

  // バッテリーの頭部を描画
  int headWidth = 3;
  M5.Lcd.fillRect(x + width, y + height / 4, headWidth, height / 2, WHITE);

  // バッテリーレベルに基づいて内部を塗りつぶす
  int fillWidth = (level * (width - 2)) / 100;
  M5.Lcd.fillRect(x + 1, y + 1, fillWidth, height - 2, GREEN);

  // テキスト背景の描画
  String levelStr = String(level) + "%";
  int textWidth = levelStr.length() * 6; // テキストの幅のおおよその計算
  int textHeight = 8; // テキストの高さのおおよその計算
  int textX = x + width / 2 - textWidth / 2; // テキストの中央揃え
  int textY = y + height / 2 - textHeight / 1; // 高さの中央
  M5.Lcd.fillRect(textX, textY, textWidth, textHeight, GREEN); // テキスト背景を緑色に塗りつぶす

  // バッテリーレベルのテキストを描画
  M5.Lcd.setTextColor(BLACK); // テキストの色を白に設定
  M5.Lcd.drawString(levelStr, textX - 3, textY, 2); // フォントサイズ2を指定
}

#endif
