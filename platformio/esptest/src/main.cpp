#include <M5GFX.h>
#include <M5Unified.h>

M5GFX display;
LGFX_Sprite app;

extern "C" void app_main() {
  M5.begin();

  display.begin();

  app.createSprite(display.width(), display.height());
  app.setTextSize(1);
  app.setCursor(0, 0);
  app.setFont(&fonts::lgfxJapanGothic_16);
  app.print("おはよう, M5Stack!");

  app.pushSprite(&display, 0, 0);
}
