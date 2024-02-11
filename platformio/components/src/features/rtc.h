#ifndef RTC_H
#define RTC_H

#include <M5Unified.h>
#include <time.h>

void initRtc() {
  M5.Rtc.begin();
  configTime(3600 * 9, 0, "ntp.jst.mfeed.ad.jp");
}

#endif
