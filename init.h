#ifndef INIT_H
#define INIT_H
#include <WiFi.h>
#include <SPIFFS.h>
#include "ESPAsyncWebServer.h"
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

void initialization();
bool startServer();
void endServer();
bool connectToWifi(const char* ssid, const char* password);
String readFile(const char * path);
void writeFile(const char * path, const char * message);

#endif
