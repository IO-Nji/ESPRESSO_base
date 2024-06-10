#include "ESP8266WiFi.h"
/*
  AsyncElegantOTA Demo Example - This example will work for both ESP8266 & ESP32 microcontrollers.
  -----
  Author: Ayush Sharma ( https://github.com/ayushsharma82 )
  
  Important Notice: Star the repository on Github if you like the library! :)
  Repository Link: https://github.com/ayushsharma82/AsyncElegantOTA
*/

// #include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>


#define LabSSID "BIO_LoFi"
#define LabPW "1011ADfive!"

String updateWebpage(uint8_t LocoState);
String generateWebPage();
String getIP();
void serverSetup(void);

AsyncWebServer server(80);
bool LocoState = LOW;

//FUBCTION DEFINITIONS

void serverSetup(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(LabSSID, LabPW);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", updateWebpage(1));
  });

  AsyncElegantOTA.begin(&server);  // Start AsyncElegantOTA
  server.begin();
}

String getIP() {
  IPAddress ip = WiFi.localIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  return ipStr;
}

// WEbpage Generation

String updateWebpage(uint8_t LocoState) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Loco Control</title>\n";
  ptr += "<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2c3e50;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESPRESS0 [Loco]</h1>\n";
  ptr += "<h2>Web Handler Interface v0.0</h2>\n";
  ptr += "<h3>Using Station(STA) Mode and OTA updates.</h3>\n";

  if (LocoState) {
    ptr += "<p>LOCO state: ON</p><a class=\"button button-off\" href=\"/update\">OFF</a>\n";
  } else {
    ptr += "<p>LOCO state: OFF</p><a class=\"button button-on\" href=\"/Handle\">ON</a>\n";
  }

  ptr += "<p>nji.io/loco</p>\n";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

