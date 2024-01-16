#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5CoreS3.h>
#include <SD.h>

extern const char* API_KEY;
const char* openai_endpoint = "https://api.openai.com/v1";

String completions(const String& content) {
  HTTPClient http;
  http.begin(String(openai_endpoint) + "/chat/completions");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(API_KEY));

  String postData = "{\"model\": \"gpt-4\", \"messages\": [{\"role\": \"user\", \"content\": \"" + content + "\"}]}";

  int httpResponseCode = http.POST(postData);
  String text = "";

  if (httpResponseCode > 0) {
    String response = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);

    JsonArray choices = doc["choices"];
    for (JsonObject choice : choices) {
      text = choice["message"]["content"].as<String>();
    }
  } else {
    text = "エラーが発生しました。";
  }

  http.end();

  return text;
}

void textToSpeech(const String& content) {
  HTTPClient http;
  http.begin(String(openai_endpoint) + "/audio/speech");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(API_KEY));

  String postData = "{\"model\": \"tts-1\", \"voice\": \"alloy\", \"input\": \"" + content + "\"}";
  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    File file = SD.open("/speech.mp3", FILE_WRITE);
    if (file) {
      http.writeToStream(&file);
      file.close();
    } else {
      M5.Lcd.println("Failed to open file on SD card");
    }
  } else {
    M5.Lcd.println("textToSpeech でエラー発生");
  }

  http.end();
}