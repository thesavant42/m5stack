#include <M5Unified.h>
#include <WiFi.h>
#include <SD.h>

#include "credentials.h"
#include "efont.h"
#include "efontM5Unified.h"
#include "efontEnableJaMini.h"
#include "button.h"
#include "openai.h"

extern const char* API_KEY;
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

ButtonManager buttonManager;

void actionButton1() {
  M5.Lcd.fillRect(0, 0, 320, 180, TFT_BLACK);
  printEfont("考え中...", 1, 0, 0);
  String content = completions("100文字程度で何かタメになる雑学をお話しして。子供が好きそうなネタで。友達に話すような感じで。本当の話で。");
  M5.Lcd.fillRect(0, 0, 320, 180, TFT_BLACK);
  printEfont(const_cast<char*>(content.c_str()), 1, 0, 0);
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
  M5.Power.begin();
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  Serial.begin(115200);

  if (!SD.begin(4)) {
    printEfont("SDカードがない", 2);
    return;
  }

  printEfont("Wifi Connecting", 2, 0, 0);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    printEfont(".", 2);
    delay(500);
  }
  M5.Lcd.fillScreen(BLACK);

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

  int32_t level = M5.Power.getBatteryLevel();
  String levelStr = String(level) + "%";
  printEfont(const_cast<char*>(levelStr.c_str()), 2, 100, 160);

  delay(10);
}
