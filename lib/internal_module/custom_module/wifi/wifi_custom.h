#ifndef wifi_custom_h
#define wifi_custom_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#define Wifi_Mode_Ap_Station WIFI_AP_STA
#define Wifi_Mode_Ap WIFI_AP
#define Ip IPAddress(192, 168, 4, 1)
#define Gateway IPAddress(192, 168, 4, 1)
#define Subnet IPAddress(255, 255, 255, 0)
#define Port 5312 
#define Update_Loop_Wifi 500
#define Delay_Time_Connect_Wifi 500

void setupWifi(const char nameAp[64], const char pskAp[64], const char nameStation[64],const char pskStation[64]);

bool isConnectWifi();

void requetstReconnectWifi();

void disconnectWifi();

int updGetPacketIncomingSize(WiFiUDP &udp, IPAddress &address, int &port);

void udpGetPacketImcoming(WiFiUDP &udp, char packet[], int size);

void udpWritePacket(WiFiUDP &udp, IPAddress address, uint32 port, JsonDocument &doc);

void udpSetPort(WiFiUDP &udp, uint32 port);

void udpWritePacket(WiFiUDP &udp, char packet[], IPAddress address, uint32 port);

void setWifiMode(WiFiMode mode);

void setWifiAp(const char nameAp[64], const char pskAp[64]);

void setWifiStation(const char nameStation[64],const char pskStation[64]);
#endif
