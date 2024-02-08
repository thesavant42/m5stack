#include <M5Unified.h>

#include "efont.h"
#include "efontM5Unified.h"
#include "efontEnableJaMini.h"

void setup() {
  M5.begin();
  
  printEfont("Hello", 1, 0, 16*0);
  printEfont("こんにちは", 2, 0, 16*1);
  printEfont("１月４日　土曜日　９時５５分", 3, 0, 16*2);

  printEfont("こんにちは", 2);
}

void loop() {
  printEfont("こんにちは", 1);
  delay(1000);
}
