#include <M5Unified.h>

#include "efont.h"
#include "efontM5Unified.h"
#include "efontEnableJaMini.h"
#include "button.h"

ButtonManager buttonManager;

void actionButton1() {
  Serial.println("Button 1 pressed");
}

void actionButton2() {
  Serial.println("Button 2 pressed");
}

Button button1(0, 140, 160, 100, "何か話して", actionButton1);
Button button2(160, 140, 160, 100, "録音", actionButton2);

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  Serial.begin(115200);

  buttonManager.addButton(button1);
  buttonManager.addButton(button2);
  buttonManager.drawButtons();
}

void loop() {
  M5.update();

  auto detail = M5.Touch.getDetail();
  if (state_name[detail.state] == "touch_begin") {
    buttonManager.handleTouch(detail.x, detail.y);
  }
}
