#ifndef APP_H
#define APP_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../api/openai.h";
#include "../components/button.h";
#include "../const.h";

extern M5GFX display;

LGFX_Sprite app;
ButtonManager buttonManager;

void drawButtons() {
  buttonManager.setSprite(&app);
  buttonManager.addButton(
      5, app.height() - 55, app.width() / 2 - 20, 50, "何かお話しして", []() {
        app.fillScreen(GRAY_COLOR);
        app.setTextColor(WHITE_COLOR, GRAY_COLOR);
        app.setCursor(0, 0);
        app.print("考え中...");
        drawButtons();
        app.pushSprite(&display, 0, STATUS_BAR_HEIGHT);

        String content = completions(
            "100文字程度で何かタメになる雑学をお話しして。子供が好きそうなネタ"
            "で。友達に話すような感じで。本当の話で。");
        app.fillScreen(GRAY_COLOR);
        app.setTextColor(WHITE_COLOR, GRAY_COLOR);
        app.setCursor(0, 0);
        app.print(content);
        drawButtons();
        app.pushSprite(&display, 0, STATUS_BAR_HEIGHT);
      });
  buttonManager.drawButtons();
}

void drawApp() {
  app.createSprite(display.width(), display.height() - STATUS_BAR_HEIGHT);
  app.fillScreen(GRAY_COLOR);
  app.setTextSize(1);
  app.setTextColor(WHITE_COLOR, GRAY_COLOR);
  app.setCursor(0, 0);
  app.setFont(&fonts::lgfxJapanGothic_16);

  drawButtons();

  app.pushSprite(&display, 0, STATUS_BAR_HEIGHT);
}

void updateApp() {
  auto detail = M5.Touch.getDetail();
  if (state_name[detail.state] == "touch_begin") {
    int localX = detail.x;
    int localY = detail.y - STATUS_BAR_HEIGHT;

    Serial.printf("x: %d, y: %d\n", localX, localY);
    buttonManager.handleTouch(localX, localY);
  }
}

#endif
