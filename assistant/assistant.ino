// const char* API_KEY = "sk-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
// const char* WIFI_SSID = "xxxxxxxxxxxxxxxxxxxxxxxx";
// const char* WIFI_PASSWORD = "xxxxxxxxxxxxxxxxxxxxxxxx";

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5CoreS3.h>
#include <SD.h>

#include "efont.h"
#include "efontM5CoreS3.h"
#include "efontEnableJaMini.h"

extern const char* API_KEY;
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

void setup() {
  M5.begin();

  printEfont("始まり！");

  if (!SD.begin(4)) {
    printEfont("SDカードない");
    return;
  }

  Serial.println("2");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("3");

  String text = completions("短い雑学を話して");
  printEfont(const_cast<char*>(text.c_str()));
  textToSpeech(text);
}

bool isPlaying = false;

void loop() {
  M5.update();

  const char* audioFileName = "/speech.mp3";

  if (SD.exists(audioFileName) && !isPlaying) {
    isPlaying = true;
    printEfont("Play!");
    // playMP3(audioFileName);
    // SD.remove(audioFileName);
    isPlaying = false;
  }

  delay(1000);
}
