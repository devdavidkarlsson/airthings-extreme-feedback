#ifndef config_web_server_h
#define config_web_server_h

#include <ESPAsyncWebServer.h>

AsyncWebServer* getServer();
void serve();
String getDeviceConfig();
String getSensorConfig();

#endif