#include <message.h>
#include <string.h>

bool deserializationJson(JsonDocument &json, char content[], messageEnum &typeMessage){
    DeserializationError error = deserializeJson(json, content);
    if(error)
        return false;
    typeMessage =(messageEnum) getParameterForMessage<uint32>(json, Key_Command);
    return true;
}

JsonDocument getMessageInformation(wifiParameter &station, wifiParameter &ap, watchModuleParameter &watchParameter){
    JsonDocument json;
    addParamterForMessage(json, Key_Brightness, watchParameter.brightness);
    addParamterForMessage(json, Key_TimeStepForDecorElement, watchParameter.timeStepForDecorElement);
    addParamterForMessage(json, Key_TimeStepForTimeElemnet, watchParameter.timeStepForTimeElement);

    addParamterForMessage(json, (String(Key_Wifi_Station) + String(Name_Keyword)).c_str(), String(station.name));
    addParamterForMessage(json, (String(Key_Wifi_Station) + String(Psk_Keyword)).c_str(), String(station.psk));

    addParamterForMessage(json, (String(Key_Wifi_AP) + String(Name_Keyword)).c_str(), String(ap.name));
    addParamterForMessage(json, (String(Key_Wifi_AP) + String(Psk_Keyword)).c_str(), String(ap.psk));

    return json;
}

uint32 getParameterTimeStepForDecorElement(JsonDocument &json){
    return getParameterForMessage<uint32>(json, Key_TimeStepForDecorElement);
}

uint32 getParameterTimeStepForTimeElement(JsonDocument &json){
        return getParameterForMessage<uint32>(json, Key_TimeStepForTimeElemnet);
}

uint32 getParameterBrightness(JsonDocument &json){
    return getParameterForMessage<uint32>(json, Key_Brightness);
}

wifiParameter getParamterWifiAp(JsonDocument &json){
    return getParamterWifi(json, Key_Wifi_AP);
}

wifiParameter getParamterWifi(JsonDocument &json, const char key[]){
    wifiParameter parameter;
    String name_key =  String(key) + String(Name_Keyword);
    String name_wifi = getParameterForMessage<String>(json, name_key.c_str());
    strcpy(parameter.name, name_wifi.c_str());
    String psk_key = String(key) + String(Psk_Keyword);
    String psk_wifi = getParameterForMessage<String>(json, psk_key.c_str());
    strcpy(parameter.psk, psk_wifi.c_str());
    return parameter;
}

wifiParameter getParamterWifiStation(JsonDocument &json){
    return getParamterWifi(json, Key_Wifi_Station);
}

template<typename T>
T getParameterForMessage(JsonDocument &json, const char key[]){
    if(json[key].is<T>())
        return json[key].as<T>();
    return T();
}

template<typename T>
void addParamterForMessage(JsonDocument &json, const char key[], T value){
    json[key] = value;
}