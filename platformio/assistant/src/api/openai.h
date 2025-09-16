#ifndef OPENAI_H
#define OPENAI_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <M5Unified.h>
#include <SD.h>

#const char* openai_endpoint = "https://api.openai.com/v1";
const char* openai_endpoint = "http://192.168.1.98:1234/v1";

String completions(const String& content) {
  HTTPClient http;
  http.begin(String(openai_endpoint) + "/chat/completions");
  http.addHeader("Content-Type", "application/json");
  #http.addHeader("Authorization", "Bearer " + String(getEnvValue("API_KEY")));
  http.setTimeout(60000);

  String postData = "{\"model\": \"qwen3-4b-instruct-2507\", \"messages\": [{\"role\": \"user\", \"content\": \"" + content + "\"}]}";

  int httpResponseCode = http.POST(postData);
  String text = "";

  String response = http.getString();
  Serial.println(response);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);

  if (httpResponseCode > 0) {
    if(doc["choices"].isNull()) {
      JsonObject error = doc["error"];
      Serial.println(error["code"].as<String>());
    } else {
      JsonArray choices = doc["choices"];
      for (JsonObject choice : choices) {
        text = choice["message"]["content"].as<String>();
      }
    }
  } else {
    Serial.println(httpResponseCode);
  }

  http.end();

  return text;
}

String textToSpeech(const String& content) {
  HTTPClient http;
  http.begin(String(openai_endpoint) + "/audio/speech");
  http.addHeader("Content-Type", "application/json");
  #http.addHeader("Authorization", "Bearer " + String(getEnvValue("API_KEY")));
  http.setTimeout(60000);

  String postData = "{\"model\": \"chatterbox\", \"voice\": \"voices/chatterbox/whywishnotfar.wav\", \"input\": \"" + content + "\"}";
  int httpResponseCode = http.POST(postData);

  String response = http.getString();

  String text = content;
  if (httpResponseCode > 0) {
    File file = SD.open("/tts.mp3", FILE_WRITE);
    if (file) {
      http.writeToStream(&file);
      file.close();
    } else {
      Serial.println("Failed to open file on SD card");
    }
  } else {
    Serial.println("Error in TextToSpeech");
    Serial.println(httpResponseCode);
  }

  http.end();

  return text;
}

#endif
