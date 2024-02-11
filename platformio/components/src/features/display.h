#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5GFX.h>

void initDisplay(M5GFX *display) {
  display->begin();
  display->setRotation(3);
}

#endif
