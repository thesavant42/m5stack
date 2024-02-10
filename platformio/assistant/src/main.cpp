#include <M5Unified.h>
#include <SD.h>

#include "efontEnableJaMini.h"
#include "efont.h"

#include "mods/font.h"
#include "mods/brightness.h"
#include "mods/battery.h"
#include "mods/env.h"
#include "mods/wifi.h"
#include "mods/button.h"
#include "api/openai.h"
#include "mods/scheduler.h"
#include "mods/scheduler.h"

Scheduler scheduler;
ButtonManager buttonManager;

void resetScreen() {
  M5.Lcd.fillRect(0, 20, 320, 160, TFT_BLACK);
}

void actionButton1() {
  resetScreen();

  puts("考え中...", 1, 0, 20);
  String content = completions("100文字程度で何かタメになる雑学をお話しして。子供が好きそうなネタで。友達に話すような感じで。本当の話で。");
  
  resetScreen();
  
  puts(const_cast<char*>(content.c_str()), 1, 0, 20);
  if (content != "") {
    String speech = textToSpeech(content);
    Serial.println(speech);
  }
}

void actionButton2() {
  Serial.println("Button 2 pressed");
}

Button button1(0, 180, 160, 60, "何か話して", actionButton1);
Button button2(160, 180, 160, 60, "録音", actionButton2);

void setup() {
  Serial.begin(115200);

  M5.Power.begin();
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  if (!SD.begin(4)) {
    puts("SDカードがない", 2);
    return;
  }

  initAutoBrightness();
  loadEnvVariables(SD, "/env.txt");
  initWifi();
  drawBattery();

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

  if (scheduler.execMs(10000)) {
    drawBattery();
  }

  if (scheduler.execMs(1000)) {
    autoBrightness();
  }
}
