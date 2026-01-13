#include "eeprom_custom.h"

void eepromBegin(){
    EEPROM.begin(Total_Size_EEPROM);
}

template<typename T>
void eepromSet(int address, T &value){
    EEPROM.put(address, value);
    EEPROM.commit();
}

template<typename T>
T eepromGet(int address){
    T parameter{};
    parameter = EEPROM.get(address, parameter);
    return parameter;
}

void eepromEnd(){
    EEPROM.end();
}

void eepromSetWifiStation(wifiParameter &wifi){
    eepromSet(Address_Wifi_Station, wifi);
}
void eepromSetWifiAp(wifiParameter & wifi){
    eepromSet(Address_Wifi_Ap, wifi);
}
void eepromSetWatchParameter(watchModuleParameter &parameter){
    eepromSet(Address_Watch_Parameter, parameter);
}

wifiParameter eepromGetWifiStation(){
    return eepromGet<wifiParameter>(Address_Wifi_Station);
}

wifiParameter eepromGetWifiAp(){
    return eepromGet<wifiParameter>(Address_Wifi_Ap);
}

watchModuleParameter eepromGetWatchModuleParameter(){
    return eepromGet<watchModuleParameter>(Address_Watch_Parameter);
}

bool isVersionValid(){
    version m_version = eepromGet<version>(Addess_Version);
    return m_version.major == Current_Version.major && m_version.minor == Current_Version.minor && m_version.patch == Current_Version.patch;
}

void eepromSetVersion(){
    version m_version = Current_Version;
    eepromSet(Addess_Version, m_version);
}