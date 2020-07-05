#ifndef __WORDCLOCK_BITMAPS_H
#define __WORDCLOCK_BITMAPS_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

typedef uint8_t bitmap[8];

struct Bitmaps {
  // digits
  static const uint8_t zero[];
  static const uint8_t one[];
  static const uint8_t two[];
  static const uint8_t three[];
  static const uint8_t four[];
  static const uint8_t five[];
  static const uint8_t six[];
  static const uint8_t seven[];
  static const uint8_t eight[];
  static const uint8_t nine[];
  static const uint8_t ten[];
  static const uint8_t eleven[];
  static const uint8_t twelve[];

  // partials
  static const uint8_t pFive[];
  static const uint8_t pTen[];
  static const uint8_t pBefore[];
  static const uint8_t pPast[];
  static const uint8_t pHalf[];

  // time
  static const uint8_t am[];
  static const uint8_t pm[];

  // weekdays
  static const uint8_t monday[];
  static const uint8_t tuesday[];
  static const uint8_t wednesday[];
  static const uint8_t thursday[];
  static const uint8_t friday[];
  static const uint8_t saturday[];
  static const uint8_t sunday[];

  // weather
  static const uint8_t c[];
  static const uint8_t hp[];
  static const uint8_t sun[];
  static const uint8_t rain[];
  static const uint8_t wind[];
  static const uint8_t cloudy[];
  static const uint8_t lightning[];
  static const uint8_t low[];
  static const uint8_t much[];

  // status
  static const uint8_t run[];
  static const uint8_t net[];
  static const uint8_t _time[];
  static const uint8_t ach[];
  static const uint8_t ach2[];

  static const bitmap *numbers[13];
};

#endif
