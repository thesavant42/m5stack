#include <M5GFX.h>

#include "const.h"

M5GFX display;

void drawStatusBar() {
  // ステータスバーの背景
  display.fillRect(0, 0, display.width(), 20, BLACK_COLOR);
  
  // バッテリー残量の表示（仮の値）
  display.setTextColor(WHITE_COLOR, BLACK_COLOR);
  display.setTextSize(1);
  display.setCursor(5, 5);
  display.print("75%");

  // Wi-Fi 状態の表示（仮のアイコン）
  display.drawCircle(display.width() - 20, 10, 5, WHITE_COLOR);
}

void drawContent() {
  // コンテンツ領域の背景
  display.fillRect(0, 20, display.width(), display.height() - 20, GREEN_COLOR);

  // コンテンツの例（テキスト）
  display.setTextColor(WHITE_COLOR, GREEN_COLOR);
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.setFont(&fonts::efontJA_12);
  display.print("何かのコンテンツが表示されます。");
}

void setup() {
  display.begin();
  display.setRotation(1); // 必要に応じて画面の向きを設定
  display.setBrightness(60);

  drawStatusBar(); // ステータスバーの描画
  drawContent(); // コンテンツの描画
}

void loop() {
  // ここにループ内で実行するコードを記述（例: ステータスバーの情報更新）
}
