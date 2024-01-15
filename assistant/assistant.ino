#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5CoreS3.h>

extern const char* API_KEY;
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

void setup() {
  initialize();
  String text = completions("hello!!");
  M5.Lcd.print(text);
}

void loop() {

}