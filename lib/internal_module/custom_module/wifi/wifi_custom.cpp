#include <custom_module/wifi/wifi_custom.h>

void setupWifi(const char nameAp[64], const char pskAp[64], const char nameStation[64],const char pskStation[64]){
    setWifiMode(Wifi_Mode_Ap_Station);
    WiFi.persistent(false);
    setWifiStation(nameStation, pskStation);    
    setWifiAp(nameAp, pskAp);
}

void setWifiMode(WiFiMode mode){
    WiFi.mode(mode);
}

void setWifiAp(const char nameAp[64], const char pskAp[64]){
    WiFi.softAPConfig(Ip, Gateway, Subnet);
    WiFi.softAP(nameAp, pskAp);
}

void setWifiStation(const char nameStation[64],const char pskStation[64]){
    WiFi.begin(nameStation, pskStation);
    /*
    for (uint8 i = 0; !isConnectWifi() && (i < Update_Loop_Wifi); i++)
        delay(Delay_Time_Connect_Wifi);
    */
}

bool isConnectWifi(){
    return WiFi.status() == WL_CONNECTED; 
}

void requetstReconnectWifi(){
    WiFi.reconnect();
}

void disconnectWifi(){
    WiFi.disconnect();
}

int updGetPacketIncomingSize(WiFiUDP &udp, IPAddress &address, int &port){
    address = udp.remoteIP();
    port = udp.remotePort();
    return udp.parsePacket();
}

void udpGetPacketImcoming(WiFiUDP &udp, char packet[], int size){
    if (size){
        udp.read(packet, size);
        packet[size] = Char_end;
    }
}

void udpSetPort(WiFiUDP &udp, uint32 port){
    udp.begin(port);
}

void udpWritePacket(WiFiUDP &udp, char packet[], IPAddress address, uint32 port){
    udp.beginPacket(address, port);
    udp.write(packet);
    udp.endPacket();
}

void udpWritePacket(WiFiUDP &udp, IPAddress address, uint32 port, JsonDocument &doc){
    udp.beginPacket(address, port);
    serializeJson(doc, udp);
    udp.endPacket();
}