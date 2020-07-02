#include "api.h"

String token;
JSONVar currentValues;

void tokenExchange() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient http;
  String response = "{}";
  http.begin(*client, "https://accounts-api.airthings.com/v1/token");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST("{\"grant_type\":\"client_credentials\", \"client_id\": \"MY_CLIENT_ID\", \"client_secret\": \"MY_CLIENT_SECRET\"}");
  
  if (httpCode > 0) {
    response = http.getString();
  } else {
    Serial.println("POST failed:" + httpCode);
  }
  http.end();
  JSONVar myObject = JSON.parse(response);
  token = myObject["access_token"];
  Serial.println("Token refreshed.");
}

void getLatestValue(String deviceId) {
  chasePixels(3);
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient http;
  String response = "{}";
  http.begin(*client, "https://ext-api.airthings.com/v1/devices/" + deviceId + "/latest-samples");
  http.addHeader("Content-Type", "application/json");  
  http.addHeader("Authorization", "Bearer " + token);
  int httpCode = http.GET();
  if (httpCode > 0) {
    response = http.getString();
  } else {
    Serial.println("GET failed:" + httpCode);
  }
  http.end();
  currentValues = JSON.parse(response);
}

int getValue(String sensor) {
    if(sensor == "temp"){
        return currentValues["data"]["temp"];
    } else if (sensor == "radon") {
        return currentValues["data"]["radonShortTermAvg"];
    } else if (sensor == "co2") {
        return currentValues["data"]["co2"];
    }
}