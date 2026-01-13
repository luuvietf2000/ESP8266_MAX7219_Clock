#ifndef eerom_custom_h
#define eerom_custom_h

#include <Arduino.h>
#include <EEPROM.h>
#include <common_strutc.h>

#define Current_Version version{0, 0, 2}

#define Addess_Version 0
#define Address_Wifi_Station (Addess_Version + Size_Version)
#define Address_Wifi_Ap (Address_Wifi_Station + Size_Wifi_Station)
#define Address_Watch_Parameter (Address_Wifi_Ap + Size_Wifi_Ap)

#define Size_Version sizeof(version)
#define Size_Wifi_Station sizeof(wifiParameter)
#define Size_Wifi_Ap sizeof(wifiParameter)
#define Size_Watch_Parameter sizeof(watchModuleParameter)

#define Total_Size_EEPROM (Size_Version + Size_Wifi_Station + Size_Wifi_Ap + Size_Watch_Parameter)


void eepromBegin();

template<typename T>
void eepromSet(int address, T &value);

template <typename T>
T eepromGet(int address);

void eepromEnd();
void eepromSetWifiStation(wifiParameter &wifi);
void eepromSetWifiAp(wifiParameter & wifi);
void eepromSetWatchParameter(watchModuleParameter &parameter);

wifiParameter eepromGetWifiStation();
wifiParameter eepromGetWifiAp();
watchModuleParameter eepromGetWatchModuleParameter();

bool isVersionValid();

void eepromSetVersion();

#endif