#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WEMOS_Matrix_GFX.h>
#include <TimeLib.h>
#include <Timezone.h>

#include "secrets.h"
#include "bitmaps.h"

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

// New bitmap to display
uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0 ,0};

// Last displayed bitmap
uint8_t oldBuffer[8] = {0, 0, 0, 0, 0, 0, 0 ,0};

// Additional connection data for a fast WiFi reconnect
uint8_t channel = 255;
uint8_t bssid[6] = { 0, 0, 0, 0, 0, 0 };

void setup() {
  matrix.setRotation(3);
  showBitmap(Bitmaps::run);

  Serial.begin(115200);
  while (!Serial) yield();

  // Disable WiFi
  WiFi.persistent(false);  // Do not store credentials in flash (prevent ageing)
  WiFi.setAutoConnect(false);
  WiFi.setAutoReconnect(false);
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  yield();

//  timeClient.setUpdateInterval(intervalNTP * 1000);
  setSyncProvider(getNtpTime);  // does an NTP request too
  setSyncInterval(intervalNTP);
}

void loop() {
  timeStatus_t ntpStatus = timeStatus();
  if (ntpStatus == timeNotSet) {
    // No time after power on yet
    showTwoBitmaps(Bitmaps::ach, Bitmaps::net);

    // try again after 30 seconds
    setSyncInterval(30);
    delay(30000);
    return;

    // or do nothing and switch off (doesn't work yet, needs code changes!)
//    ESP.deepSleep(0, WAKE_RF_DISABLED);
  }

  if (ntpStatus == timeNeedsSync && (millis() - lastSync) > (24 * 60 * 60 * 1000)) {
    // No NTP answer for 24 hours
    showTwoBitmaps(Bitmaps::ach, Bitmaps::_time);
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
  clear();

  if (minute % 10 >= 5) {
    drawBitmap(Bitmaps::pFive);
    Serial.print(F("fünf"));
  }

  if ((minute >= 10 && minute < 25) || (minute >= 40 && minute < 55)) {
    drawBitmap(Bitmaps::pTen);
    Serial.print(F("zehn"));
  }

  if ((minute >= 5 && minute < 20) || (minute >= 35 && minute < 45)) {
    drawBitmap(Bitmaps::pPast);
    Serial.print(F(" nach "));
  } else if ((minute >= 20 && minute < 30) || minute >= 45) {
    drawBitmap(Bitmaps::pBefore);
    Serial.print(F(" vor "));
  }

  if (minute >= 20 && minute < 45) {
    drawBitmap(Bitmaps::pHalf);
    Serial.print(F("halb "));
  }

  if (minute >= 20) hour++;

  if (hour > 12) hour = hour % 12;
  if (hour == 0) hour = 12;
  drawBitmap(*Bitmaps::numbers[hour]);
  Serial.println(hour);

  writeDisplayWithVerticalLineTransition();
}

void clear() {
  for (uint8 i = 0; i < 8; i++) {
    buffer[i] = 0;
  }
  matrix.clear();
}

// Displayes the old and the new bitmap with a separating vertical line moving from left to right.
void writeDisplayWithVerticalLineTransition() {
  for (int i = 0; i < 8; i++) {
    // bit set where the line should be displayed
    uint8_t barMask = 0x80 >> i;
    // unset bits where the new and set bits where the old bitmap should be displayed
    uint8_t oldNewMask = 0xFF >> i;

    for (int j = 0; j < 8; j++) {
      oldBuffer[j] &= oldNewMask;
      oldBuffer[j] |= barMask | (buffer[j] & ~oldNewMask);
    }

    matrix.clear();
    matrix.drawBitmap(0, 0, oldBuffer, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(35);
  }
  writeDisplay();
}

void writeDisplay() {
  for (int i = 0; i < 8; i++) oldBuffer[i] = buffer[i];
  matrix.clear();
  matrix.drawBitmap(0, 0, buffer, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void drawBitmap(const uint8_t word[]) {
  for (int i = 0; i < 8; i++) {
    buffer[i] |= pgm_read_byte(&word[i]);
  }
}

void showBitmap(const uint8_t bitmap[]) {
  clear();
  drawBitmap(bitmap);
  writeDisplay();

  // after displaying text the time display needs to be restored
  lastDisplayTime = 0;
}

void showTwoBitmaps(const uint8_t bitmap1[], const uint8_t bitmap2[]) {
  clear();
  drawBitmap(bitmap1);
  drawBitmap(bitmap2);
  writeDisplay();

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
      showBitmap(Bitmaps::net);
    Serial.print(F("\n\nConnecting to "));
    Serial.println(ssid);
    WiFi.forceSleepWake();
    yield();
    WiFi.mode(WIFI_STA);
    if (channel < 255) {
      // fast connect
      WiFi.begin(ssid, password, channel, bssid, true);
    } else {
      WiFi.begin(ssid, password);
    }

    Serial.print(F("Waiting for connection"));

    int connectTimeout = 300;
    while (!WiFi.isConnected())
    {
      if (channel < 255 && connectTimeout == 200) {
        // If fast connect failed, reset WIFI and do a normal connect
        WiFi.disconnect();
        delay(10);
        WiFi.forceSleepBegin();
        yield();
        WiFi.forceSleepWake();
        yield();
        WiFi.begin(ssid, password);
      }

      Serial.print(F("."));
      if (--connectTimeout <= 0)
      {
        Serial.println();
        Serial.print(F("WiFi connect timeout: "));
        Serial.println(WiFi.status());

        disconnectAndDisableWiFi();

        return 0;
      }
      delay(50);
    }
  }

  Serial.println();
  Serial.println(F("WiFi connected"));

  // Print the IP address
  Serial.print(F("Local IP: "));
  Serial.println(WiFi.localIP());

  // Save channel and bssid for a fast connect next time
  channel = WiFi.channel();
  memcpy(bssid, WiFi.BSSID(), 6);

//  if (noTime)
    showBitmap(Bitmaps::_time);
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

  disconnectAndDisableWiFi();

  return time;
}

void disconnectAndDisableWiFi() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  yield();
}
