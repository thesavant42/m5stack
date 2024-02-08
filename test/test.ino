#include <M5CoreS3.h>
// #include "efont.h"
// #include "efontM5CoreS3.h"
// #include "efontEnableJa.h"

void setup() {
  M5.begin();
  // Serial.begin(115200);
}

void loop() {
  M5.update();

  Serial.println("hello");
  M5.Lcd.print(".");
  // printEfont("あいうえお");

  delay(1000);
}
