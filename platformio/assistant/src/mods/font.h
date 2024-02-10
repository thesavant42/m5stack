#ifndef __EFONT_M5_H__
#define __EFONT_M5_H__

#define EFONT_USED

#include <M5Unified.h>
#include "efont.h"

//#define EFONT_DEBUG

static uint8_t currentTextSize = 1;

static int lastX[255] = {0}, lastY[255] = {0};
static int currentLayer = 0; 

void puts(char *str, uint8_t layer, int x = -1, int y = -1, int textsize = 1, uint16_t color = TFT_WHITE, uint16_t bgcolor = TFT_BLACK) {
  if (layer != currentLayer || x >= 0 && y >= 0) {
    if (x >= 0 && y >= 0) {
      M5.Lcd.setCursor(x, y);
      lastX[layer] = x;
      lastY[layer] = y;
    } else {
      M5.Lcd.setCursor(lastX[layer], lastY[layer]);
    }
    currentLayer = layer;
  }
  if (textsize != currentTextSize) {
    M5.Lcd.setTextSize(textsize);
    currentTextSize = textsize;
  }
  M5.Lcd.setTextColor(color, bgcolor);

  byte font[32];

  while (*str != 0x00) {
    if (*str == '\n') {
      M5.Lcd.setCursor(0, M5.Lcd.getCursorY() + 16 * textsize);
      str++;
      continue;
    }

    uint16_t strUTF16;
    str = efontUFT8toUTF16(&strUTF16, str);
    getefontData(font, strUTF16);

    int width = (strUTF16 < 0x0100) ? 8 : 16;
    width *= textsize;

    if (M5.Lcd.getCursorX() + width > M5.Lcd.width()) {
      M5.Lcd.setCursor(0, M5.Lcd.getCursorY() + 16 * textsize);
    }

#ifdef EFONT_DEBUG
    Serial.printf("str : U+%04X\n", strUTF16);
#endif

    for (int row = 0; row < 16; row++) {
      uint16_t fontdata = (font[row * 2] << 8) | font[row * 2 + 1];
      for (int col = 0; col < 16; col++) {
        if (fontdata & (1 << (15 - col))) {
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

    M5.Lcd.setCursor(M5.Lcd.getCursorX() + width, M5.Lcd.getCursorY());

    lastX[layer] = M5.Lcd.getCursorX();
    lastY[layer] = M5.Lcd.getCursorY();
  }
}

#endif
