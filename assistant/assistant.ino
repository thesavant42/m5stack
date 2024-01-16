// const char* API_KEY = "sk-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
// const char* WIFI_SSID = "xxxxxxxxxxxxxxxxxxxxxxxx";
// const char* WIFI_PASSWORD = "xxxxxxxxxxxxxxxxxxxxxxxx";

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
  }

  String text = completions("何か短い雑学をお話しください");
  M5.Lcd.print(text);
  textToSpeech(text);
}

bool isPlaying = false;

void loop() {
  M5.update();

  const char* audioFileName = "/speech.mp3";

  if (SD.exists(audioFileName) && !isPlaying) {
    isPlaying = true;
    M5.Lcd.print("Play!");
    playMP3(audioFileName);
    // SD.remove(audioFileName);
    isPlaying = false;
  }

  delay(1000);
}
