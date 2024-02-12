#ifndef APP_H
#define APP_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../components/button.h";
#include "../const.h";

extern M5GFX display;

LGFX_Sprite app;
ButtonManager buttonManager;

void drawButtons() {
  buttonManager.setSprite(&app);
  buttonManager.addButton(10, 10, 100, 50, "Button1",
                          []() { Serial.println("Button1 pressed"); });
  buttonManager.drawButtons();
}

void drawApp() {
  app.createSprite(display.width(), display.height() - STATUS_BAR_HEIGHT);
  app.fillScreen(GRAY_COLOR);

  app.setTextSize(1);
  app.setTextColor(WHITE_COLOR, GRAY_COLOR);
  app.setCursor(0, 0);
  app.setFont(&fonts::lgfxJapanGothic_16);
  app.printf("APP");

  drawButtons();

  app.pushSprite(&display, 0, STATUS_BAR_HEIGHT);
  app.deleteSprite();
}

void updateApp() {
  auto detail = M5.Touch.getDetail();
  if (state_name[detail.state] == "touch_begin") {
    buttonManager.handleTouch(detail.x, detail.y);
  }
}

#endif
