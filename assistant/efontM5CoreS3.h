#ifndef __EFONT_M5_H__
#define __EFONT_M5_H__

#define EFONT_USED

#include <M5CoreS3.h> // M5CoreS3 用のヘッダーファイルに変更
#include "efont.h"

//#define EFONT_DEBUG

// グローバル変数で現在のテキストサイズを追跡
static uint8_t currentTextSize = 1;

void printEfont(char *str, int x = -1, int y = -1, int textsize = 1, uint16_t color = TFT_WHITE, uint16_t bgcolor = TFT_BLACK) {
  if (x >= 0 && y >= 0) {
    CoreS3.Display.setCursor(x, y);
  }
  if (textsize != currentTextSize) {
    CoreS3.Display.setTextSize(textsize);
    currentTextSize = textsize; // テキストサイズを更新
  }
  CoreS3.Display.setTextColor(color, bgcolor);

  byte font[32];
  
  while (*str != 0x00) {
    // 改行処理
    if (*str == '\n') {
      CoreS3.Display.setCursor(0, CoreS3.Display.getCursorY() + 16 * textsize); // カーソルを次の行の開始位置に移動
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
    if (CoreS3.Display.getCursorX() + width > CoreS3.Display.width()) {
      CoreS3.Display.setCursor(0, CoreS3.Display.getCursorY() + 16 * textsize); // カーソルを次の行の開始位置に移動
    }

#ifdef EFONT_DEBUG
    Serial.printf("str : U+%04X\n", strUTF16);
#endif

    // 文字の描画
    for (int row = 0; row < 16; row++) {
      uint16_t fontdata = (font[row * 2] << 8) | font[row * 2 + 1];
      for (int col = 0; col < 16; col++) {
        if (fontdata & (1 << (15 - col))) {
          int drawX = CoreS3.Display.getCursorX() + col * textsize;
          int drawY = CoreS3.Display.getCursorY() + row * textsize;
          for (int dx = 0; dx < textsize; dx++) {
            for (int dy = 0; dy < textsize; dy++) {
              CoreS3.Display.drawPixel(drawX + dx, drawY + dy, color);
            }
          }
        }
      }
    }

    // カーソルを文字分進める
    CoreS3.Display.setCursor(CoreS3.Display.getCursorX() + width, CoreS3.Display.getCursorY());
  }
}

#endif // __EFONT_M5_H__
