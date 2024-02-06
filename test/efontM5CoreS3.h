#ifndef __EFONT_M5CORES3_H__
#define __EFONT_M5CORES3_H__

#define EFONT_USED

#include <M5CoreS3.h> // M5CoreS3 用のヘッダーファイルに変更
#include "efont.h"

//#define EFONT_DEBUG

// グローバル変数で現在のテキストサイズを追跡
static uint8_t currentTextSize = 1;

void printEfont(char *str, int x = -1, int y = -1, int textsize = 1, uint16_t color = TFT_WHITE, uint16_t bgcolor = TFT_BLACK) {
  if (x >= 0 && y >= 0) {
    M5.Lcd.setCursor(x, y);
  }
  if (textsize != currentTextSize) {
    M5.Lcd.setTextSize(textsize);
    currentTextSize = textsize;
  }
  M5.Lcd.setTextColor(color, bgcolor);

  byte font[32];

  while (*str != 0x00) {
    // 改行処理
    if (*str == '\n') {
      M5.Lcd.setCursor(0, M5.Lcd.getCursorY() + 16 * textsize); // カーソルを次の行の開始位置に移動
      str++;
      continue;
    }

    uint16_t strUTF16;
    str = efontUFT8toUTF16(&strUTF16, str);
    getefontData(font, strUTF16);

    // 文字横幅の計算
    int width = (strUTF16 < 0x0100) ? 8 : 16; // 半角は8、全角は16
    width *= textsize; // テキストサイズに応じて調整

    // 現在位置 + 文字幅がディスプレイ幅を超える場合、改行する
    if (M5.Lcd.getCursorX() + width > M5.Lcd.width()) {
      M5.Lcd.setCursor(0, M5.Lcd.getCursorY() + 16 * textsize); // カーソルを次の行の開始位置に移動
    }

#ifdef EFONT_DEBUG
    Serial.printf("str : U+%04X\n", strUTF16);
#endif

    // 文字の描画
    for(int row = 0; row < 16; row++) {
      // 16ビットのフォントデータを取得
      uint16_t fontdata = (font[row * 2] << 8) | font[row * 2 + 1];
      for(int col = 0; col < 16; col++) {
        // 各ビットをチェックし、対応するピクセルを描画
        if(fontdata & (1 << (15 - col))) { // 0x8000 >> col から 1 << (15 - col) に変更
          int drawX = M5.Lcd.getCursorX() + col * textsize;
          int drawY = M5.Lcd.getCursorY() + row * textsize;
          for (int dx = 0; dx < textsize; dx++) {
            for (int dy = 0; dy < textsize; dy++) {
              M5.Lcd.drawPixel(drawX + dx, drawY + dy, color);
            }
          }
        }
      }
    }

    // カーソルを文字分進める
    M5.Lcd.setCursor(M5.Lcd.getCursorX() + width, M5.Lcd.getCursorY());
  }
}

#endif // __EFONT_M5CORES3_H__
