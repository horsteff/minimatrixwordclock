#ifndef __WORDCLOCK_WORDS_H
#define __WORDCLOCK_WORDS_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

struct Words {
  static constexpr const uint8_t ach[] =
  {
      0x00,
      B00001110,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ach2[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B11100000
  };
  static constexpr const uint8_t ahne[] =
  {
      0x00,
      0x00,
      B01000000,
      B00111000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t alberei[] =
  {
      0x00,
      0x00,
      B01110000,
      B00001000,
      B00001110,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t bei[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B11000000,
      B01000000,
      0x00
  };
  static constexpr const uint8_t bieder[] =
  {
      0x00,
      0x00,
      0x00,
      B00001000,
      B01111000,
      B10000000,
      0x00,
      0x00
  };
  static constexpr const uint8_t bin[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B10000000,
      B01100000,
      0x00
  };
  static constexpr const uint8_t drin[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00011011,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t du[] =
  {
      0x00,
      0x00,
      0x00,
      B00000100,
      B00010000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t echt[] =
  {
      B00000100,
      B00000111,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t echt2[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B10000000,
      B01110000,
  };
  static constexpr const uint8_t ehe[] =
  {
      0x00,
      0x00,
      B01100000,
      B00100000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ein[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00000111,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ein2[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B11100000,
      0x00
  };
  static constexpr const uint8_t einzel[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00010010,
      B11101000,
      0x00
  };
  static constexpr const uint8_t er[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000011
  };
  static constexpr const uint8_t es[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000001,
      B00000010
  };
  static constexpr const uint8_t fach[] =
  {
      B00010000,
      B00001110,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t fahne[] =
  {
      B10000000,
      0x00,
      B01000000,
      B00111000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t fein[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000001,
      B11100000,
      0x00
  };
  static constexpr const uint8_t ha[] =
  {
      0x00,
      0x00,
      B11000000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t hahn[] =
  {
      0x00,
      B11000000,
      B00110000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t he[] =
  {
      0x00,
      0x00,
      B10000000,
      B01000000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t he2[] =
  {
      0x00,
      0x00,
      0x00,
      B00100000,
      B00100000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t horn[] =
  {
      0x00,
      B01110000,
      B10000000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ich[] =
  {
      B00000010,
      B00000100,
      B00001000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ihn[] =
  {
      0x00,
      0x00,
      0x00,
      B00110000,
      B01000000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t ihr[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000010,
      B00000101
  };
  static constexpr const uint8_t insel[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000010,
      B01111000,
      0x00
  };
  static constexpr const uint8_t lach[] =
  {
      0x00,
      B00001110,
      B00100000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t lacht[] =
  {
      0x00,
      B00001111,
      B00100000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t na[] =
  {
      0x00,
      B00011000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t nacht[] =
  {
      0x00,
      B00011111,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t net[] =
  {
      0x00,
      B00000001,
      B00000100,
      B00010000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t neu[] =
  {
      0x00,
      0x00,
      0x00,
      B00011100,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t nicht[] =
  {
      0x00,
      B00010111,
      B00001000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t nie[] =
  {
      0x00,
      B00010000,
      B00001100,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t rein[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00001111,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t roehr[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00001000,
      B00000100,
      B00000010,
      B00000001
  };
  static constexpr const uint8_t run[] =
  {
      0x00,
      0x00,
      0x00,
      B00000110,
      B00001000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t sacht[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000001,
      B11110000
  };
  static constexpr const uint8_t sei[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B10000000,
      B01000000,
      B01000000,
      0x00
  };
  static constexpr const uint8_t seicht[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B10000000,
      B01000000,
      B01000000,
      B01110000
  };
  static constexpr const uint8_t selber[] =
  {
      0x00,
      0x00,
      B00110000,
      B01001000,
      B10001000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t sense[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B11000000,
      B00111000,
      0x00,
      0x00
  };
  static constexpr const uint8_t sie[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B11100000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t sieh[] =
  {
      0x00,
      0x00,
      0x00,
      B00100000,
      B11100000,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t vieh[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00000010,
      B00001110
  };
  static constexpr const uint8_t vorbei[] =
  {
      0x00,
      B11100000,
      B00010000,
      B00001000,
      B00000010,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t vorn[] =
  {
      0x00,
      B11110000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t wein[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      B00000111,
      B00001000,
      0x00,
      0x00
  };
  static constexpr const uint8_t wir[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00001000,
      0x00,
      B00000101
  };
  static constexpr const uint8_t woelfe[] =
  {
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      B00001111,
      B10000000,
      0x00
  };
  static constexpr const uint8_t zahn[] =
  {
      0x00,
      0x00,
      B01000000,
      B10110000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t zaehne[] =
  {
      0x00,
      0x00,
      B01000000,
      B11111000,
      0x00,
      0x00,
      0x00,
      0x00
  };
  static constexpr const uint8_t zeit[] =
  {
      0x00,
      0x00,
      0x00,
      B10000000,
      0x00,
      B01000000,
      B01000000,
      B00010000
  };
  static constexpr const uint8_t zorn[] =
  {
      0x00,
      B01110000,
      B10000000,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00
  };
};

#endif
