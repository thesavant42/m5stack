#include <M5CoreS3.h>
#include "efont.h"
#include "efontM5CoreS3.h"
#include "efontEnableJa.h"

void setup() {
  M5.begin();

  printEfont("Hello");
  printEfont("こんにちは");
}

void loop() {
  M5.update();

  printEfont("あいうえお");

  delay(1000);
}
