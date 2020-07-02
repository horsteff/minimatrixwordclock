# Mini mini german wordclock with a WEMOS (LOLIN) D1 mini and the 8x8 Matrix LED Shield

* developed using the Arduino IDE (https://www.arduino.cc/)
* board definition: "LOLIN(WEMOS) D1 R2 & mini"
* gets time by NTP
* connects to WLAN only during NTP requests
* can work without WLAN connection after a successful initial NTP request

## Parts:

WEMOS (LOLIN) D1 mini: https://docs.wemos.cc/en/latest/d1/d1_mini.html
Matrix LED Shield: https://docs.wemos.cc/en/latest/d1_mini_shiled/matrix_led.html

## Libraries:

Wemos Matrix Adafruit GFX by Thomas O Fredericks: https://github.com/thomasfredericks/wemos_matrix_gfx
Adafruit GFX Library by Adafruit: https://github.com/adafruit/Adafruit-GFX-Library
NTPClient by Fabrice Weinberg: https://github.com/arduino-libraries/NTPClient
Time by Michael Margolis/Paul Stoffregen: https://github.com/PaulStoffregen/Time
Timezone by Jack Christensen: https://github.com/JChristensen/Timezone
