#include <M5CoreS3.h>
#include "efont.h"
#include "efontM5CoreS3.h"
#include "efontEnableJa.h"

void setup() {
  M5.begin();
  M5.Lcd.setCursor(0, 0);

  printEfont("Hello");
  printEfont("こんにちは");
}

void loop() {
  M5.update();

  printEfont("あ");

  delay(1000);
}
