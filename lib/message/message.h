#ifndef message_h
#define message_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <common_strutc.h>

#define Key_Wifi_AP "AP "
#define Key_Wifi_Station "Station "
#define Name_Keyword "Name"
#define Psk_Keyword "Psk"
#define Key_Brightness "Brightness"
#define Key_TimeStepForDecorElement "Time Step Decor Element"
#define Key_TimeStepForTimeElemnet "Time Step Time Element"
#define Key_Command "Command"

typedef enum{
    Set_WifiStation,
    Set_WifiAp,
    Set_TimeStepForDecorElement,
    Set_TimeStepForTimeElement,
    Set_Brightness
} messageEnum;

bool deserializationJson(JsonDocument &json, char content[], messageEnum &typeMessage);

JsonDocument getMessageInformation(wifiParameter &station, wifiParameter &ap, watchModuleParameter &watchParameter);

uint32 getParameterTimeStepForDecorElement(JsonDocument &json);

uint32 getParameterTimeStepForTimeElement(JsonDocument &json);

uint32 getParameterBrightness(JsonDocument &json);

wifiParameter getParamterWifiAp(JsonDocument &json);

wifiParameter getParamterWifi(JsonDocument &json, const char key[]);

wifiParameter getParamterWifiStation(JsonDocument &json);

template<typename T>
T getParameterForMessage(JsonDocument &json, const char key[]);

template<typename T>
void addParamterForMessage(JsonDocument &json, const char key[], T value);

#endif