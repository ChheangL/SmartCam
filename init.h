#ifndef INIT_H
#define INIT_H
#include <WiFi.h>
#include <SPIFFS.h>
#include "ESPAsyncWebServer.h"

bool startServer();
void endServer();
bool connectToWifi(const char* ssid, const char* password);
String readFile(const char * path);
void writeFile(const char * path, const char * message);

#endif
