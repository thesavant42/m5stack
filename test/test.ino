#include <M5CoreS3.h>

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  M5.Lcd.println("Start");
}

void loop() {
  M5.update();

  M5.Lcd.println(".");

  delay(1000);
}
