#ifndef CLOCK_H
#define CLOCK_H

#include <M5GFX.h>
#include <M5Unified.h>

#include "../const.h"

extern M5GFX display;

void drawClock(int x, int y) {
  //   RTC_TimeTypeDef nowTime;
  //   RTC_DateTypeDef nowDate;
  //   M5.Rtc.GetTime(&nowTime);  // 現在時刻の取得
  //   M5.Rtc.GetDate(&nowDate);  // 現在日付の取得

  //   char timeStr[20];
  //   sprintf(timeStr, "%04d/%02d/%02d %02d:%02d:%02d", nowDate.Year,
  //   nowDate.Month,
  //           nowDate.Date, nowTime.Hours, nowTime.Minutes, nowTime.Seconds);

  //   display.setCursor(x, y);
  //   display.setTextColor(WHITE);
  //   display.setTextSize(1);
  //   display.println(timeStr);  // 時刻をディスプレイに表示
}

#endif
