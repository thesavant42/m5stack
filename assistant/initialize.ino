void initialize() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  CoreS3.Display.startWrite();
  CoreS3.Display.setRotation(1);
  CoreS3.Display.setTextDatum(top_center);
  CoreS3.Display.setTextColor(WHITE);
  CoreS3.Display.setFont(&fonts::FreeSansBoldOblique12pt7b);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
