#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WEMOS_Matrix_GFX.h>
#include <TimeLib.h>
#include <Timezone.h>

#include "secrets.h"
#include "numbers.h"
#include "parts.h"
#include "words.h"

const char* ssid     = WIFI_SSID;
const char* password = WIFI_PWD;

const long utcOffsetInSeconds = 0;

MLED matrix(2);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP); 

TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };
Timezone CE(CEST, CET);
TimeChangeRule * tcr;

unsigned long intervalNTP = 60 * 60 * 1000; // Request NTP time every hour
unsigned long prevNTP = 0;
unsigned long lastNTPResponse = 0;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);

  drawWord(WORDS_NEU);

  while (!Serial) yield();

  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
//  WiFi.setAutoConnect(true);
//  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  drawWord(WORDS_NET);
  Serial.println(F("Waitung for connection"));
  
  int ConnectTimeout = 30;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
    Serial.print(WiFi.status());
    if (--ConnectTimeout <= 0)
    {
      drawWord(WORDS_ACHACH);
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

  drawWord(WORDS_DRIN);
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Print the IP address
  Serial.println(WiFi.localIP());

  drawWord(WORDS_ZEIT);
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

  if (currentMillis - prevNTP > intervalNTP) { // If a minute has passed since last NTP request
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
    }
  }

  time_t localtime = CE.toLocal(timeClient.getEpochTime(), &tcr);
  unsigned long now = timeClient.getHours() * 60 + timeClient.getMinutes();
  if (lastTime != now) {
    Serial.print(F("Current UTC time:\t"));
    Serial.println(timeClient.getFormattedTime());

    lastTime = now;
    uint8_t buffer[8];
    for (int i = 0; i < 8; i++) buffer[i] = 0;
    
//    int minutes = timeClient.getMinutes();
    int minutes = minute(localtime);
    int addHour = 0;
    if (minutes >= 5 && minutes < 10) {
      overlay(buffer, parts[PART_FIVE], 8);
      overlay(buffer, parts[PART_PAST], 8);
      Serial.print(F("Fünf nach "));
    } else if (minutes >= 10 && minutes < 15) {
      overlay(buffer, parts[PART_TEN], 8);
      overlay(buffer, parts[PART_PAST], 8);
      Serial.print(F("Zehn nach "));
    } else if (minutes >= 15 && minutes < 20) {
      overlay(buffer, parts[PART_FIVE], 8);
      overlay(buffer, parts[PART_TEN], 8);
      overlay(buffer, parts[PART_PAST], 8);
      Serial.print(F("Fünfzehn nach "));
    } else if (minutes >= 20 && minutes < 25) {
      overlay(buffer, parts[PART_TEN], 8);
      overlay(buffer, parts[PART_BEFORE], 8);
      overlay(buffer, parts[PART_HALF], 8);
      addHour = 1;
      Serial.print(F("Zehn vor halb "));
    } else if (minutes >= 25 && minutes < 30) {
      overlay(buffer, parts[PART_FIVE], 8);
      overlay(buffer, parts[PART_BEFORE], 8);
      overlay(buffer, parts[PART_HALF], 8);
      addHour = 1;
      Serial.print(F("Fünf vor halb "));
    } else if (minutes >= 30 && minutes < 35) {
      overlay(buffer, parts[PART_HALF], 8);
      addHour = 1;
      Serial.print(F("Halb "));
    } else if (minutes >= 35 && minutes < 40) {
      overlay(buffer, parts[PART_FIVE], 8);
      overlay(buffer, parts[PART_PAST], 8);
      overlay(buffer, parts[PART_HALF], 8);
      addHour = 1;
      Serial.print(F("Fünf nach halb "));
    } else if (minutes >= 40 && minutes < 45) {
      overlay(buffer, parts[PART_TEN], 8);
      overlay(buffer, parts[PART_PAST], 8);
      overlay(buffer, parts[PART_HALF], 8);
      addHour = 1;
      Serial.print(F("Zehn nach halb "));
    } else if (minutes >= 45 && minutes < 50) {
      overlay(buffer, parts[PART_FIVE], 8);
      overlay(buffer, parts[PART_TEN], 8);
      overlay(buffer, parts[PART_BEFORE], 8);
      addHour = 1;
      Serial.print(F("Fünfzehn vor "));
    } else if (minutes >= 50 && minutes < 55) {
      overlay(buffer, parts[PART_TEN], 8);
      overlay(buffer, parts[PART_BEFORE], 8);
      addHour = 1;
      Serial.print(F("Zehn vor "));
    } else if (minutes >= 55) {
      overlay(buffer, parts[PART_FIVE], 8);
      overlay(buffer, parts[PART_BEFORE], 8);
      addHour = 1;
      Serial.print(F("Fünf vor "));
    }
  
//    int hours = timeClient.getHours() + addHour;
    int hours = hour(localtime) + addHour;
    if (hours > 12) hours = hours % 12;
    if (hours == 0) hours = 12;
    overlay(buffer, numbers[hours - 1], 8);
    Serial.println(hours);

    matrix.clear();
    matrix.drawBitmap(0, 0, buffer, 8, 8, LED_ON);
    matrix.writeDisplay();
  }

  delay(1000);
}

void overlay(uint8_t *dest, const uint8_t *src, size_t num) {
  for (int i = 0; i < num; i++) {
    uint8_t b = dest[i];
    b |=  pgm_read_byte(src + i);
    dest[i] = b;
  }
}

void drawWord(int index) {
  matrix.clear();
  matrix.drawBitmap(0, 0, words[index], 8, 8, LED_ON);
  matrix.writeDisplay();
}
