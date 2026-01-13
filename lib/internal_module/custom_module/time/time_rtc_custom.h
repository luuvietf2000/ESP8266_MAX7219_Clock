#ifndef time_rtc_h
#define time_rtc_h

#include <ESP8266WiFi.h>

#define UTC_Time (7 * 3600)
#define DaylightOffset 0
#define Server_One "pool.ntp.org"
#define Server_Two "time.nist.gov"
#define Update_Loop_RTC 10
#define Year_Current 2026
#define Year_Start 1970
#define Year_Current_Unix_Time ((Year_Current - Year_Start) * 365 * 24 * 60 * 60) 
#define Delay_Time_RTC_Sync 500

void timeSync();
tm getTmTime();
bool isTimeRtcValid();

#endif