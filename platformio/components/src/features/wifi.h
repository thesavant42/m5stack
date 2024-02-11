#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

#include "env.h"
#include "font.h"

void initWifi() {
  p("Wifi Connecting", WHITE_COLOR, GRAY_COLOR);

  WiFi.begin(getEnvValue("WIFI_SSID"), getEnvValue("WIFI_PASSWORD"));
  while (WiFi.status() != WL_CONNECTED) {
    p(".", WHITE_COLOR, GRAY_COLOR);
    delay(500);
  }

  // OpenAI API の DNS サーバーを指定
  IPAddress dns(104, 18, 6, 192);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, dns);
}

#endif
