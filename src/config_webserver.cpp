
#include "config_webserver.h"

String ssid;
String wpa;
String deviceId;
String sensor;

const char* SSID_PARAM_INPUT_1 = "ssid";
const char* WPA_PARAM_INPUT_2 = "wpa";
const char* DEVICE_ID_PARAM_INPUT_3 = "deviceId";
const char* SENSOR_PARAM_INPUT_4 = "sensor";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>🐧 Pingwing 3000 🐧</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h1>Pingwing 3000</h1>
  <!--
  <form action="/get">
    SSID: <input type="text" name="ssid">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    WPA: <input type="text" name="wpa">
    <input type="submit" value="Submit">
  </form><br> -->
    <form action="/get">
    Device: <input type="text" name="deviceId">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Sensor: <input type="text" name="sensor" value="temp">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "The pingwing you are looking for is: Not found");
}

AsyncWebServer* getServer() {
    return &server;
}

String getDeviceConfig() {
  return deviceId;
}

String getSensorConfig(){
  return sensor;
}

void serve() {
    Serial.println("Serving webpage.");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    if (request->hasParam(SSID_PARAM_INPUT_1)) {
      inputMessage = request->getParam(SSID_PARAM_INPUT_1)->value();
      inputParam = SSID_PARAM_INPUT_1;
      ssid = inputMessage;
    }
    else if (request->hasParam(WPA_PARAM_INPUT_2)) {
      inputMessage = request->getParam(WPA_PARAM_INPUT_2)->value();
      inputParam = WPA_PARAM_INPUT_2;
      wpa = inputMessage;
    }
    else if (request->hasParam(DEVICE_ID_PARAM_INPUT_3)) {
      inputMessage = request->getParam(DEVICE_ID_PARAM_INPUT_3)->value();
      inputParam = DEVICE_ID_PARAM_INPUT_3;
      deviceId = inputMessage;
    }
    else if (request->hasParam(SENSOR_PARAM_INPUT_4)) {
      inputMessage = request->getParam(SENSOR_PARAM_INPUT_4)->value();
      inputParam = SENSOR_PARAM_INPUT_4;
      sensor = inputMessage;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/html", "Pingwing configured from input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });

  server.onNotFound(notFound);
  server.begin();
}