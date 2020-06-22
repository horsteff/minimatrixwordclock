#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WEMOS_Matrix_GFX.h>
#include <TimeLib.h>
#include <Timezone.h>

#include "secrets.h"
#include "numbers.h"
#include "partials.h"
#include "words.h"

// WLAN credentials
const char* ssid     = WIFI_SSID;
const char* password = WIFI_PWD;

// Request NTP interval in seconds
const unsigned long intervalNTP = 60 * 60;

MLED matrix(4);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP); 

TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };
Timezone CE(CEST, CET);

// Last displayed time in minutes
int lastDisplayTime = 0;

// True until the first successful NTP request
bool noTime = true;

// Last successful NTP request in system millis
unsigned long lastSync = 0;

void setup() {
  showBitmap(Words::run);

  Serial.begin(115200);
  while (!Serial) yield();

  WiFi.mode(WIFI_STA);
//  WiFi.setAutoConnect(true);
//  WiFi.setAutoReconnect(true);

//  timeClient.setUpdateInterval(intervalNTP * 1000);
  setSyncProvider(getNtpTime);  // does an NTP request too
  setSyncInterval(intervalNTP);
}

void loop() {
  timeStatus_t ntpStatus = timeStatus();
  if (ntpStatus == timeNotSet) {
    // No time after power on yet
    showTwoBitmaps(Words::ach2, Words::net);

    // try again after 30 seconds
    setSyncInterval(30);
    delay(30000);
    return;

    // or do nothing and switch off
//    ESP.deepSleep(0, WAKE_RF_DISABLED);
  }

  if (ntpStatus == timeNeedsSync && (millis() - lastSync) > (24 * 60 * 60 * 1000)) {
    // No NTP answer for 24 hours
    showTwoBitmaps(Words::ach, Words::zeit);
    delay(500);
  }

  // Calculate localtime with timezone
  time_t localtime = CE.toLocal(now());
  Serial.print(F("Current time:\t"));
  Serial.println(formatTime(hour(localtime), minute(localtime)));
  int hours = hourFormat12(localtime);
  int minutes = minute(localtime);
  int seconds = second(localtime);

  // Display should change in the middle of 5-minute periods -> shift display time by 2.5 minutes (150 seconds)
  int displaySecond = seconds + 150;
  int displayHour = hours;
  int displayMinute = minutes + (displaySecond / 60);
  displaySecond %= 60;
  if (displayMinute >= 60) {
    displayMinute %= 60;
    displayHour++;
    if (displayHour > 12) displayHour = 1;
  }

  // Display needs to update every 5 minutes only
  int displayNow = displayHour * 60 + ((displayMinute / 5) * 5);
  if (lastDisplayTime != displayNow) {
    lastDisplayTime = displayNow;
    showTime(displayHour, displayMinute);
  }

  // wait until the next possible display change (every 5 minute)
  int secondsToNextUpdate = ((displayNow + 5) * 60) - ((((displayHour * 60) + displayMinute) * 60) + displaySecond);
  if (secondsToNextUpdate > 0) {
    Serial.print(F("Seconds to next display update: "));
    Serial.println(secondsToNextUpdate);
    delay(secondsToNextUpdate * 1000 + 100);
  }
}

void showTime(int hour, int minute) {
  matrix.clear();

  if (minute % 10 >= 5) {
    drawBitmap(Partials::five);
    Serial.print(F("fünf"));
  }

  if ((minute >= 10 && minute < 25) || (minute >= 40 && minute < 55)) {
    drawBitmap(Partials::ten);
    Serial.print(F("zehn"));
  }

  if ((minute >= 5 && minute < 20) || (minute >= 35 && minute < 45)) {
    drawBitmap(Partials::past);
    Serial.print(F(" nach "));
  } else if ((minute >= 20 && minute < 30) || minute >= 45) {
    drawBitmap(Partials::before);
    Serial.print(F(" vor "));
  }

  if (minute >= 20 && minute < 45) {
    drawBitmap(Partials::half);
    Serial.print(F("halb "));
  }

  if (minute >= 20) hour++;

  if (hour > 12) hour = hour % 12;
  if (hour == 0) hour = 12;
  drawBitmap(*Numbers::digits[hour - 1]);
  Serial.println(hour);

  matrix.writeDisplay();
}

void drawBitmap(const uint8_t word[]) {
  matrix.drawBitmap(0, 0, word, 8, 8, LED_ON);
}

void showBitmap(const uint8_t bitmap[]) {
  matrix.clear();
  matrix.drawBitmap(0, 0, bitmap, 8, 8, LED_ON);
  matrix.writeDisplay();

  // after displaying text the time display needs to be restored
  lastDisplayTime = 0;
}

void showTwoBitmaps(const uint8_t bitmap1[], const uint8_t bitmap2[]) {
  matrix.clear();
  drawBitmap(bitmap1);
  drawBitmap(bitmap2);
  matrix.writeDisplay();

  // after displaying text time display needs to be restored
  lastDisplayTime = 0;
}

String formatTime(int hour, int minute) {
  String hourString = (hour < 10) ? "0" + String(hour) : String(hour);
  String minuteString = (minute < 10) ? "0" + String(minute) : String(minute);
  return hourString + ":" + minuteString;
}

time_t getNtpTime() {
  if (!WiFi.isConnected()) {
//    if (noTime)
      showBitmap(Words::net);
    Serial.print(F("\n\nConnecting to "));
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    Serial.print(F("Waiting for connection"));

    int ConnectTimeout = 30;
    while (!WiFi.isConnected())
    {
      delay(500);
      Serial.print(F("."));
      if (--ConnectTimeout <= 0)
      {
        Serial.println();
        Serial.print(F("WiFi connect timeout: "));
        Serial.println(WiFi.status());

        WiFi.disconnect(true);

        return 0;
      }
    }
  }

  Serial.println();
  Serial.println(F("WiFi connected"));

  // Print the IP address
  Serial.print(F("Local IP: "));
  Serial.println(WiFi.localIP());

  if (noTime)
    showTwoBitmaps(Words::net, Words::zeit);
  timeClient.begin();
  bool gotTime = timeClient.update();
  timeClient.end();
  time_t time = 0;
  if (gotTime) {
    Serial.print(F("Got UTC time:\t"));
    Serial.println(timeClient.getFormattedTime());
    noTime = false;
    lastSync = millis();
    setSyncInterval(intervalNTP);
    time = timeClient.getEpochTime();
  }

  WiFi.disconnect(true);

  return time;
}
