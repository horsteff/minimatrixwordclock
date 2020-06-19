#ifndef __WORDCLOCK_PARTIALS_H
#define __WORDCLOCK_PARTIALS_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

struct Partials {
  static constexpr const uint8_t five[] =
  {
      B11110000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ten[] =
  {
      B00001111,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t before[] =
  {
      0x00,
      B11100000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t past[] =
  {
      0x00,
      B00011110,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t half[] =
  {
      0x00,
      0x00,
      B11110000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
};

#endif
