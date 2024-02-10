#ifndef BUTTON_H
#define BUTTON_H

#include <M5Unified.h>

#include "efont.h"
#include "efontM5Unified.h"
#include "efontEnableJaMini.h"

static constexpr const char* state_name[16] = {
            "none", "touch", "touch_end", "touch_begin",
            "___",  "hold",  "hold_end",  "hold_begin",
            "___",  "flick", "flick_end", "flick_begin",
            "___",  "drag",  "drag_end",  "drag_begin"};

// ボタンがタッチされたときに実行する関数の型を定義
typedef void (*ButtonAction)();

class Button {
public:
    int x, y, width, height;
    String label;
    ButtonAction action;

    Button(int x, int y, int width, int height, String label, ButtonAction action)
    : x(x), y(y), width(width), height(height), label(label), action(action) {}

    // ボタンをLCDに描画
    void draw() {
        M5.Lcd.drawRect(x, y, width, height, WHITE);
        printEfont(const_cast<char*>(label.c_str()), 0, x + 20, y + height / 3);
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

    void addButton(const Button& button) {
        buttons.push_back(button);
    }

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

#endif // BUTTON_H
