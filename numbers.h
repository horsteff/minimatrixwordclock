#ifndef __WORDCLOCK_NUMBERS_H
#define __WORDCLOCK_NUMBERS_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

typedef uint8_t bitmap[8];

struct Numbers {
  static constexpr const uint8_t one[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B11110000,
      0x00
  };
  static constexpr const uint8_t two[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00000110,
      B00011000,
      0x00,
      0x00
  };
  static constexpr const uint8_t three[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00011110,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t four[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00001111
  };
  static constexpr const uint8_t five[] =
  {
      0x00,
      0x00,
      0x01,
      0x01,
      0x01,
      0x01,
      0x00,
      0x00
  };
  static constexpr const uint8_t six[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00011111,
      0x00
  };
  static constexpr const uint8_t seven[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B11100000,
      B11100000,
      0x00,
      0x00
  };
  static constexpr const uint8_t eight[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B11110000
  };
  static constexpr const uint8_t nine[] =
  {
      0x00,
      0x00,
      0x00,
      B00011110,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ten[] =
  {
      0x00,
      0x00,
      0x00,
      B11110000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t eleven[] =
  {
      0x00,
      0x00,
      B00000111,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t twelve[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00011111,
      0x00,
      0x00
  };

  static constexpr const bitmap *digits[] = {
    &one, &two, &three, &four, &five, &six, &seven, &eight, &nine, &ten, &eleven, &twelve
  };
};

#endif
