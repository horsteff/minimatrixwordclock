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

  showWord(Words::run);

  while (!Serial) yield();

  Serial.print(F("\n\nConnecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
//  WiFi.setAutoConnect(true);
//  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  showWord(Words::net);
  Serial.println(F("Waitung for connection"));
  
  int ConnectTimeout = 30;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
    Serial.print(WiFi.status());
    if (--ConnectTimeout <= 0)
    {
      showWord(Words::achach);
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

  showWord(Words::drin);
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Print the IP address
  Serial.println(WiFi.localIP());

  showWord(Words::zeit);
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

  time_t localtime = CE.toLocal(timeClient.getEpochTime(), &tcr);
  int seconds = second(localtime);
  int minutes = minute(localtime);
  int hours = hour(localtime);

  int now = hours * 60 + minutes;
  if (lastTime != now) {
    Serial.print(F("Current UTC time:\t"));
    Serial.println(timeClient.getFormattedTime());

    lastTime = now;
    uint8_t buffer[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    
    if (minutes % 10 >= 5) {
      overlay(buffer, Partials::five);
      Serial.print(F("fünf"));
    }

    if ((minutes >= 10 && minutes < 25) || (minutes >= 40 && minutes < 55)) {
      overlay(buffer, Partials::ten);
      Serial.print(F("zehn"));
    }

    if ((minutes >= 5 && minutes < 20) || (minutes >= 35 && minutes < 45)) {
      overlay(buffer, Partials::past);
      Serial.print(F(" nach "));
    } else if ((minutes >= 20 && minutes < 30) || minutes >= 45) {
      overlay(buffer, Partials::before);
      Serial.print(F(" vor "));
    }

    if (minutes >= 20 && minutes < 45) {
      overlay(buffer, Partials::half);
      Serial.print(F("halb "));
    }

    if (minutes >= 20) hours++;

    if (hours > 12) hours = hours % 12;
    if (hours == 0) hours = 12;
    overlay(buffer, *Numbers::digits[hours - 1]);
    Serial.println(hours);

    matrix.clear();
    matrix.drawBitmap(0, 0, buffer, 8, 8, LED_ON);
    matrix.writeDisplay();
  }

  // wait until the next possible display change (every 5 minutes)
  delay(((300 - (((minutes * 60) + seconds) % 300)) * 1000) + 100);
}

void overlay(uint8_t *dest, const uint8_t *src) {
  for (int i = 0; i < 8; i++) {
    uint8_t b = dest[i];
    b |=  pgm_read_byte(src + i);
    dest[i] = b;
  }
}

void showWord(const uint8_t word[]) {
  matrix.clear();
  matrix.drawBitmap(0, 0, word, 8, 8, LED_ON);
  matrix.writeDisplay();
}
