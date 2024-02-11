#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "M5CoreS3.h"

Ltr5xx_Init_Basic_Para device_init_base_para = LTR5XX_BASE_PARA_CONFIG_DEFAULT;

uint16_t read_ps_value;
uint16_t read_als_value;

void initAutoBrightness() {
  if (!CoreS3.Ltr553.begin(&device_init_base_para)) {
    while (1) {
      delay(10);
    }
  }
  CoreS3.Ltr553.setPsMode(LTR5XX_PS_ACTIVE_MODE);
  CoreS3.Ltr553.setAlsMode(LTR5XX_ALS_ACTIVE_MODE);
}

void autoBrightness() {
  read_als_value = CoreS3.Ltr553.getAlsValue();
  if (read_als_value > 100) {
    read_als_value = 100;
  }
  M5.Lcd.setBrightness(read_als_value + 50);
}

#endif
