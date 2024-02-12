#ifndef BUTTON_H
#define BUTTON_H

#include <M5Unified.h>

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
    sprite->drawRect(x, y, width, height, TFT_WHITE);  // 枠を描画
    sprite->setTextColor(TFT_WHITE, TFT_BLACK);        // 文字色を設定
    sprite->setCursor(x + 5, y + height / 2 - 4);  // ラベルの表示位置を設定
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
