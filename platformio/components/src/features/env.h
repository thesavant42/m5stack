#ifndef ENV_H
#define ENV_H

#include <FS.h>
#include <SD.h>

#include <map>
#include <string>

#include "font.h"

std::map<String, String> envVariables;

void initEnv(fs::FS &fs, const char *path) {
  if (!SD.begin(4)) {
    p("SDカードが認識されていません");
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

String getEnvValue(const String &key) {
  if (envVariables.find(key) != envVariables.end()) {
    return envVariables[key];
  }
  return String("");
}

#endif
