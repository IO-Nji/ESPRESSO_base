#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
// provides ESP8266 specific Wi-Fi routines we are calling to connect to network #include "WiFiUdp.h" //handles sending and receiving of UDP packages

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);
String arr_days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void timeSetup() {
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  timeClient.update();
}

// NTP Time hour since Midnight
int getTimeHour() {
  return timeClient.getHours();
}

// NTP Time Minutes since 00:59
int getTimeMin() {
  return timeClient.getMinutes();
}

// NTP Time Day of week since Sunday [0-6]
String getDayWeek() {
  return arr_days[timeClient.getDay()];
}

// NTP Time Date of the Month [0-31]
int getDayMonth() {

  //Get a time structure for epoch time and extract Month date
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  return monthDay;

}