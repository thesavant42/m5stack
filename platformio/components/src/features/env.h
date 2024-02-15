#ifndef ENV_H
#define ENV_H

#include <FS.h>
#include <SD.h>

#include <map>
#include <string>

#include "../credentials.h"

extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;
extern const char* API_KEY;

std::map<String, String> envVariables;

void initEnv(fs::FS& fs, const char* path) {
  envVariables["WIFI_SSID"] = WIFI_SSID;
  envVariables["WIFI_PASSWORD"] = WIFI_PASSWORD;
  envVariables["API_KEY"] = API_KEY;
  return;

  if (!SD.begin(4)) {
    Serial.println("SDカードが認識されていません");
    envVariables["WIFI_SSID"] = WIFI_SSID;
    envVariables["WIFI_PASSWORD"] = WIFI_PASSWORD;
    envVariables["API_KEY"] = API_KEY;
    return;
  }

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available()) {
    String line = file.readStringUntil('\n');
    int index = line.indexOf('=');
    if (index != -1) {
      String key = line.substring(0, index);
      String value = line.substring(index + 1);
      envVariables[key] = value;
    }
  }
  file.close();
}

String getEnvValue(const String& key) {
  if (envVariables.find(key) != envVariables.end()) {
    return envVariables[key];
  }
  return String("");
}

#endif
