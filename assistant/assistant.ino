#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5CoreS3.h>
#include <SD.h>

extern const char* API_KEY;
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  if (!SD.begin(4)) {
    M5.Lcd.println("No SD Card");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }

  M5.Lcd.println("completions");
  String text = completions("hello!!");
  M5.Lcd.print(text);
  textToSpeech(text);
}

void loop() {

}