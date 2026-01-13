#include "custom_module/time/time_rtc_custom.h"

void timeSync(){
    configTime(UTC_Time, DaylightOffset, Server_One, Server_Two);

    /*
    for (uint8 i = 0; isTimeRtcValid() && i < Update_Loop_RTC; i++) 
        delay(Delay_Time_RTC_Sync);
    
    struct tm timeinfo;
    time_t now = time(nullptr);
    localtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
    */
}

tm getTmTime(){
    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo); 
    return timeinfo;
}

bool isTimeRtcValid(){
    time_t now = time(nullptr);
    return now > Year_Current_Unix_Time;
}