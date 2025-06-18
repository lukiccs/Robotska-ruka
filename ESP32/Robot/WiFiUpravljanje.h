#ifndef WIFIUPRAVLJANJE_H
#define WIFIUPRAVLJANJE_H

#include <WiFi.h>

//Globalne promenljive
extern const char* ssid;
extern const char* password;
extern WiFiServer serverWIFI;

//Deklaracija funkcija
void WiFiSetup();
void WiFiPrijem();

#endif