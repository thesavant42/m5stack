#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

#include "env.h"

extern M5GFX display;

void initWifi() {
  LGFX_Sprite sprite;

  sprite.createSprite(display.width(), display.height());
  sprite.fillScreen(BLACK_COLOR);

  sprite.setTextColor(WHITE_COLOR, BLACK_COLOR);
  sprite.setFont(&fonts::lgfxJapanGothic_16);
  sprite.print("wifi connecting...");

  Serial.println(getEnvValue("WIFI_SSID"));
  WiFi.begin(getEnvValue("WIFI_SSID"), getEnvValue("WIFI_PASSWORD"));

  sprite.pushSprite(&display, 0, 0);

  while (WiFi.status() != WL_CONNECTED) {
    sprite.print(".");
    sprite.pushSprite(&display, 0, 0);
    delay(500);
  }

  sprite.deleteSprite();

  // OpenAI API の DNS サーバーを指定
  IPAddress dns(104, 18, 6, 192);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, dns);
}

#endif
