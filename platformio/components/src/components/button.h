#ifndef BUTTON_H
#define BUTTON_H

#include <M5Unified.h>

#include "../const.h"

static constexpr const char* state_name[16] = {
    "none", "touch", "touch_end", "touch_begin",
    "___",  "hold",  "hold_end",  "hold_begin",
    "___",  "flick", "flick_end", "flick_begin",
    "___",  "drag",  "drag_end",  "drag_begin"};

typedef void (*ButtonAction)();

class Button {
 public:
  int x, y, width, height;
  String label;
  ButtonAction action;
  LGFX_Sprite* sprite;  // 描画対象のディスプレイまたはスプライトのポインタ

  Button(int x, int y, int width, int height, String label, ButtonAction action,
         LGFX_Sprite* sprite)
      : x(x),
        y(y),
        width(width),
        height(height),
        label(label),
        action(action),
        sprite(sprite) {}

  // ボタンをLCDまたはスプライトに描画
  void draw() {
    sprite->fillRoundRect(x, y, width, height, 10, GREEN_COLOR);
    sprite->setTextColor(WHITE_COLOR, GREEN_COLOR);
    int textWidth = sprite->textWidth(label);
    int textX = x + (width - textWidth) / 2;
    int textY = y + (height - 16) / 2;
    sprite->setCursor(textX, textY);
    sprite->print(label);
  }

  // 指定された座標がボタン内か判定
  bool contains(int tx, int ty) {
    return (tx >= x && tx <= x + width && ty >= y && ty <= y + height);
  }

  // ボタンがタッチされたときのアクションを実行
  void press() {
    if (action) action();
  }
};

#include <vector>

class ButtonManager {
 public:
  std::vector<Button> buttons;
  LGFX_Sprite* sprite;

  void addButton(int x, int y, int width, int height, String label,
                 ButtonAction action) {
    buttons.emplace_back(x, y, width, height, label, action, sprite);
  }

  void setSprite(LGFX_Sprite* sprite) { this->sprite = sprite; }

  void drawButtons() {
    for (auto& button : buttons) {
      button.draw();
    }
  }

  void handleTouch(int x, int y) {
    for (auto& button : buttons) {
      if (button.contains(x, y)) {
        button.press();
        break;
      }
    }
  }
};

#endif
