#include <Arduino.h>
#include <ArduinoJson.h>
#include <DNSServer.h>

#include <ESPAsyncWiFiManager.h>

#include <config_webserver.h>
#include <pixels.h>
#include <api.h>


int score = 0;
unsigned long timer = 0;
bool hasWifi = false;
bool startup = true;
int updateInterval = 60000;

void setup() {
  Serial.begin(9600);
  setupPixels();
  setAllPixels(0, 0, 255);
  Serial.println("Starting WiFi");
  DNSServer dns;  
  AsyncWiFiManager wifiManager(getServer(),&dns);
  wifiManager.autoConnect("AT", "MY_WPA_KEY");
  Serial.println("WiFi connected");
  chasePixels(100);
  clearPixels();
  serve();
}

void loop() {
  if((millis() - timer) >= updateInterval || startup) {
    startup = false;
    timer = millis();

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connecting to server");
      tokenExchange();
      getLatestValue(getDeviceConfig());

      String sensor = getSensorConfig();
      int value = getValue(sensor);
      Serial.println("Showing: " + sensor + ". Value: " + value );

      if(sensor == "temp") {
        if(value > 25) {
          setAllPixels(255, 0, 0);
        } else if (value > 18) {
          setAllPixels(128, 128, 128);
        } else {
          setAllPixels(0, 255, 0);
        }
      } else if (sensor == "co2") {
        if(value > 1000) {
          setAllPixels(255, 0, 0);
        } else if (value > 500) {
          setAllPixels(128, 128, 128);
        } else {
          setAllPixels(0, 255, 0);
        }
      } else if (sensor == "radon") {
        if(value > 150) {
          setAllPixels(255, 0, 0);
        } else if (value > 100) {
          setAllPixels(128, 128, 128);
        } else {
          setAllPixels(0, 255, 0);
        }
      }

      else {
        setAllPixels(0,0,0);
      }
          
    }
    else {
      hasWifi = false;
      Serial.println("WiFi couldn't connect");
      blinkPixels(0, 0, 255, 5);
    }
  }
}
