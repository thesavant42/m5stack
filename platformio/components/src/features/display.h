#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5GFX.h>

extern M5GFX display;

void initDisplay() {
  display.begin();
  display.setRotation(0);
  display.fillScreen(GRAY_COLOR);
}

#endif
