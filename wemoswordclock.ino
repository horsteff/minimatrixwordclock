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

const char* ssid     = WIFI_SSID;
const char* password = WIFI_PWD;

MLED matrix(2);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP); 

TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };
Timezone CE(CEST, CET);
TimeChangeRule * tcr;

const unsigned long intervalNTP = 60 * 60 * 1000; // Request NTP time every hour

unsigned long prevNTP = 0;
unsigned long lastNTPResponse = 0;

int lastDisplayTime = 0;

void setup() {
  Serial.begin(115200);

  showBitmap(Words::run);

  while (!Serial) yield();

  Serial.print(F("\n\nConnecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
//  WiFi.setAutoConnect(true);
//  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  showBitmap(Words::net);
  Serial.println(F("Waitung for connection"));
  
  int ConnectTimeout = 30;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
    Serial.print(WiFi.status());
    if (--ConnectTimeout <= 0)
    {
      showTwoWords(Words::ach2, Words::net);
      Serial.println();
      Serial.println(F("WiFi connect timeout"));
      
      pinMode(BUILTIN_LED, OUTPUT);
      for (;;) {
        digitalWrite(BUILTIN_LED, LOW);
        delay(2000);
        digitalWrite(BUILTIN_LED, HIGH);
        delay(2000);
      }
    }
    yield();
  }

  showBitmap(Words::drin);
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Print the IP address
  Serial.println(WiFi.localIP());

  showBitmap(Words::zeit);
  timeClient.setUpdateInterval(intervalNTP);
  timeClient.begin();

  Serial.println(F("Sending first NTP request ..."));
  if (timeClient.update()) {
    Serial.print(F("Got UTC time:\t"));
    Serial.println(timeClient.getFormattedTime());
  } else {
    Serial.println(F("NTP request failed"));
  }

  matrix.intensity = 4;
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevNTP > intervalNTP) { // If a NTP interval has passed since last NTP request
    prevNTP = currentMillis;
    Serial.print(F("Current UTC time:\t"));
    Serial.println(timeClient.getFormattedTime());
    Serial.println(F("Sending NTP request ..."));
    bool gotTime = timeClient.update();

    if (gotTime) {                                  // If a new timestamp has been received
      setTime(timeClient.getEpochTime());
      Serial.print(F("Got new NTP UTC time:\t"));
      Serial.println(timeClient.getFormattedTime());
      lastNTPResponse = currentMillis;
    } else if ((currentMillis - lastNTPResponse) > 3600000) {
      Serial.println(F("More than 1 hour since last NTP response. Rebooting."));
      Serial.flush();
      ESP.reset();
    } else if (intervalNTP > 600000) {
      // on unsuccessful NTP try again after 10 min if NTP interval is above 10 min
      prevNTP = currentMillis - intervalNTP + 600000;
    }
  }

  // Calculate localtime with timezone
  Serial.print(F("Current UTC time:\t"));
  Serial.println(timeClient.getFormattedTime());
  time_t localtime = CE.toLocal(timeClient.getEpochTime(), &tcr);
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
  uint8_t buffer[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  if (minute % 10 >= 5) {
    overlay(buffer, Partials::five);
    Serial.print(F("fünf"));
  }

  if ((minute >= 10 && minute < 25) || (minute >= 40 && minute < 55)) {
    overlay(buffer, Partials::ten);
    Serial.print(F("zehn"));
  }

  if ((minute >= 5 && minute < 20) || (minute >= 35 && minute < 45)) {
    overlay(buffer, Partials::past);
    Serial.print(F(" nach "));
  } else if ((minute >= 20 && minute < 30) || minute >= 45) {
    overlay(buffer, Partials::before);
    Serial.print(F(" vor "));
  }

  if (minute >= 20 && minute < 45) {
    overlay(buffer, Partials::half);
    Serial.print(F("halb "));
  }

  if (minute >= 20) hour++;

  if (hour > 12) hour = hour % 12;
  if (hour == 0) hour = 12;
  overlay(buffer, *Numbers::digits[hour - 1]);
  Serial.println(hour);

  showBitmap(buffer);
}

void overlay(uint8_t dest[], const uint8_t *src) {
  for (int i = 0; i < 8; i++) dest[i] |= pgm_read_byte(src + i);
}

void showBitmap(const uint8_t word[]) {
  matrix.clear();
  matrix.drawBitmap(0, 0, word, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void showTwoWords(const uint8_t word1[], const uint8_t word2[]) {
  uint8_t buffer[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  overlay(buffer, word1);
  overlay(buffer, word2);
  showBitmap(buffer);
}
