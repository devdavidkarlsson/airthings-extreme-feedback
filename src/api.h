#ifndef api_h
#define api_h

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Arduino_JSON.h>
#include <pixels.h>


void tokenExchange();
void getLatestValue(String deviceId); 
int getValue(String sensor);

#endif