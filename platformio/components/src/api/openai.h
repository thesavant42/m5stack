#ifndef OPENAI_H
#define OPENAI_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <M5Unified.h>
#include <SD.h>

#include "../features/env.h"

const char* openai_endpoint = "https://api.openai.com/v1";

String completions(const String& content) {
  HTTPClient http;
  http.begin(String(openai_endpoint) + "/chat/completions");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(getEnvValue("API_KEY")));
  http.setTimeout(60000);

  String postData =
      "{\"model\": \"gpt-4-turbo-preview\", \"messages\": [{\"role\": "
      "\"user\", \"content\": \"" +
      content + "\"}]}";

  int httpResponseCode = http.POST(postData);
  String text = "";

  String response = http.getString();
  Serial.println(response);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);

  if (httpResponseCode > 0) {
    if (doc["choices"].isNull()) {
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
  http.addHeader("Authorization", "Bearer " + String(getEnvValue("API_KEY")));
  http.setTimeout(60000);

  String postData =
      "{\"model\": \"tts-1\", \"voice\": \"alloy\", \"input\": \"" + content +
      "\"}";
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
    Serial.println("TextToSpeech でエラー発生");
    Serial.println(httpResponseCode);
  }

  http.end();

  return text;
}

#endif
