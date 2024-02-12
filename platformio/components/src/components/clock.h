#ifndef CLOCK_H
#define CLOCK_H

#include <M5GFX.h>
#include <M5Unified.h>
#include <time.h>

#include "../const.h"

extern M5GFX display;

void drawClock(LGFX_Sprite* sprite, int x, int y) {
  time_t now = time(NULL);
  struct tm* timeinfo = localtime(&now);

  sprite->setTextSize(1);
  sprite->setTextColor(WHITE_COLOR, BLACK_COLOR);
  sprite->setCursor(x, y);
  sprite->setFont(&fonts::lgfxJapanGothic_16);

  if (timeinfo->tm_year == 99) {
    sprite->printf("--:--");
  } else {
    sprite->printf("%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
  }
}

#endif
