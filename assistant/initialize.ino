void initialize() {
  M5.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // M5.Lcd.print(".");
  }

  // M5.Lcd.print("!");
}
