#include <Arduino.h>

#include <watch_module/watch_module.h>
#include <custom_module/eerom/eeprom_custom.h>
#include <custom_module/time/time_rtc_custom.h>
#include <custom_module/wifi/wifi_custom.h>
#include <message.h>
#include <common_strutc.h>

#define cs D2
#define size 4
#define Ap_Name "Esp_Watch"
#define Ap_Psk "12345678a"
#define Station_Name "VIETTEL"
#define Station_Psk "12345678a"
#define WatchTimeStepForDecorElemtent 200
#define WatchTimeStepForTimeElemtent 100
#define WatchBrightness Intensity_Min
#define Buffer_Size 128

watch_module watch;
wifiParameter station, ap;
watchModuleParameter watchParameter;
WiFiUDP udp;
bool isRtcSync;

void eepromSetup();
void requestDisconnect();
void udpHandle();
void handleMessage(messageEnum &type, JsonDocument &doc);
void handleMessageGetInformation(IPAddress &address, int &port);
void handleTimeStepForDecorElement(JsonDocument &json);
void handleTimeStepForTimeElement(JsonDocument &json);
void handleBrightness(JsonDocument &json);
void handlemessageSetWifiStation(JsonDocument &json);
void handleMessageSetWifiAp(JsonDocument &json);

void setup() {
    isRtcSync = false;
    eepromBegin();
    eepromSetup();
    String name = String(ap.name) + String(ESP.getChipId());
    setupWifi(name.c_str(), ap.psk, station.name, station.psk);
    timeSync();
    udpSetPort(udp, Port);
    watch.begin(cs, size);
    watch.setTimeStepForTimeUnit(watchParameter.timeStepForTimeElement);
    watch.setTimeStepForDecorUnit(watchParameter.timeStepForDecorElement);
    watch.setIntensity(watchParameter.brightness);
}

void loop() {
    watch.requestUpdate();
    requestDisconnect();
    udpHandle();
}

void handleMessageSetWifiAp(JsonDocument &json){
    wifiParameter parameter = getParamterWifiAp(json);
    ap = parameter;
    eepromSetWifiAp(ap);
    setWifiAp(ap.name, ap.psk);
    udpSetPort(udp, Port);
}

void handlemessageSetWifiStation(JsonDocument &json){
    wifiParameter parameter = getParamterWifiStation(json);
    station = parameter;
    eepromSetWifiStation(station);
    ESP.reset();
}
void handleMessageGetInformation(IPAddress &address, int &port){
    JsonDocument reply;
    reply = getMessageInformation(station, ap, watchParameter);
    udpWritePacket(udp, address, port, reply);
}
void handleTimeStepForDecorElement(JsonDocument &json){
    uint32 timeStep = getParameterTimeStepForDecorElement(json);
    watch.setTimeStepForDecorUnit(timeStep);
    watchParameter.timeStepForDecorElement = timeStep;
    eepromSetWatchParameter(watchParameter);
}
void handleTimeStepForTimeElement(JsonDocument &json){
    uint32 timeStep = getParameterTimeStepForTimeElement(json);
    watch.setTimeStepForTimeUnit(timeStep);
    watchParameter.timeStepForTimeElement = timeStep;
    eepromSetWatchParameter(watchParameter);
}
void handleBrightness(JsonDocument &json){
    uint32 brightness = getParameterBrightness(json);
    watch.setIntensity(brightness);
    watchParameter.brightness = brightness;
    eepromSetWatchParameter(watchParameter);
}

void handleMessage(messageEnum &type, JsonDocument &doc){
    switch (type){
        case Set_TimeStepForDecorElement:
            handleTimeStepForDecorElement(doc);
            break;
        case Set_TimeStepForTimeElement:
            handleTimeStepForTimeElement(doc);
            break;
        case Set_Brightness:
            handleBrightness(doc);
            break;
        case Set_WifiAp:
            handleMessageSetWifiAp(doc);
            break;
        case Set_WifiStation:
            handlemessageSetWifiStation(doc);
    }
}

void udpHandle(){
    IPAddress address;
    int port;
    int sizePacket = updGetPacketIncomingSize(udp, address, port);
    char buffer[Buffer_Size];
    JsonDocument json;
    messageEnum type;
    bool isJsonValid = false;
    if(sizePacket){
        udpGetPacketImcoming(udp, buffer, sizePacket);
        isJsonValid = deserializationJson(json, buffer, type);
    }
    if(isJsonValid){
        handleMessage(type, json);
        handleMessageGetInformation(address, port);
    }
}

void requestDisconnect(){
    if(!isRtcSync && isTimeRtcValid()){
        disconnectWifi();
        setWifiMode(Wifi_Mode_Ap);
        setWifiAp(ap.name, ap.psk);
        isRtcSync = true;
    }
}

void eepromSetup(){
    bool isDataValid = isVersionValid();
    if(!isDataValid){
        eepromSetVersion();
        ap = wifiParameter{Ap_Name, Ap_Psk};
        station = wifiParameter{Station_Name, Station_Psk};
        watchParameter = watchModuleParameter{WatchTimeStepForTimeElemtent, WatchTimeStepForDecorElemtent, WatchBrightness};
        eepromSetWifiAp(ap);
        eepromSetWifiStation(station);
        eepromSetWatchParameter(watchParameter);
        Serial.println("init");
    } else{
        ap = eepromGetWifiAp();
        station = eepromGetWifiStation();
        watchParameter = eepromGetWatchModuleParameter();
        Serial.println("init exist");
    }
}