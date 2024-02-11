#ifndef FONT_H
#define FONT_H

#include <M5GFX.h>

extern M5GFX display;

void initFont() { display.setFont(&fonts::efontJA_16); }

void p(const char *str) { display.println(str); }

#endif
