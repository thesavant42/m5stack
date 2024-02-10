#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

#include "efont.h"
#include "mods/efontM5Unified.h"

void initWifi() {
  printEfont("Wifi Connecting", 2, 0, 0);
  WiFi.begin(getEnvValue("WIFI_SSID"), getEnvValue("WIFI_PASSWORD"));
  while (WiFi.status() != WL_CONNECTED) {
    printEfont(".", 2);
    delay(500);
  }
  M5.Lcd.fillScreen(BLACK);

  // OpenAI API の DNS サーバーを指定
  IPAddress dns(104, 18, 6, 192);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, dns);
}

#endif
