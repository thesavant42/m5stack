#include <M5Unified.h>

#include "efont.h"
#include "efontM5Unified.h"
#include "efontEnableJaMini.h"

void setup() {
  M5.begin();
  
  printEfont("Hello");
  printEfont("こんにちは", 100, 16*1);
  printEfont("１月４日　土曜日　９時５５分", 0, 10);
}

void loop() {

}
