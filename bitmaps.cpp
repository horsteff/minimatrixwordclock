#include "bitmaps.h"

// digits
const uint8_t Bitmaps::zero[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B01000000,
    0x00,
    0x00
};
const uint8_t Bitmaps::one[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00011110,
    0x00
};
const uint8_t Bitmaps::two[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00011000,
    B00011000,
    0x00
};
const uint8_t Bitmaps::three[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B01111000,
    0x00
};
const uint8_t Bitmaps::four[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B01111000,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::five[] =
{
    0x00,
    0x00,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    0x00,
    0x00
};
const uint8_t Bitmaps::six[] =
{
    0x00,
    0x00,
    0x00,
    B11111000,
    0x00,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::seven[] =
{
    0x00,
    0x00,
    0x00,
    B00001110,
    B00000111,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::eight[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
};
const uint8_t Bitmaps::nine[] =
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
const uint8_t Bitmaps::ten[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B01111000
};
const uint8_t Bitmaps::eleven[] =
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
const uint8_t Bitmaps::twelve[] =
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

// partials
const uint8_t Bitmaps::pFive[] =
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
const uint8_t Bitmaps::pTen[] =
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
const uint8_t Bitmaps::pBefore[] =
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
const uint8_t Bitmaps::pPast[] =
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
const uint8_t Bitmaps::pHalf[] =
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

// time
const uint8_t Bitmaps::am[] =
{
    0x00,
    B00001000,
    B00001000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::pm[] =
{
    0x00,
    B00000001,
    B00001000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};

// weekdays
const uint8_t Bitmaps::monday[] =
{
    0x00,
    0x00,
    B00001000,
    0x00,
    0x00,
    B01000000,
    0x00,
    0x00
};
const uint8_t Bitmaps::tuesday[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B01001000,
    0x00
};
const uint8_t Bitmaps::wednesday[] =
{
    0x00,
    0x00,
    B00001000,
    B00000100,
    0x00,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::thursday[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B01000000,
    B01000000,
    0x00
};
const uint8_t Bitmaps::friday[] =
{
    B10000000,
    B00100000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::saturday[] =
{
    0x00,
    0x00,
    0x00,
    B10000000,
    B10000000,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::sunday[] =
{
    0x00,
    0x00,
    0x00,
    B10000000,
    0x00,
    B01000000,
    0x00,
    0x00
};

// weather
const uint8_t Bitmaps::c[] =
{
    0x00,
    B00000100,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::hp[] =
{
    0x00,
    B00000011,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
const uint8_t Bitmaps::sun[] =
{
    0x00,
    0x00,
    0x00,
    B10000000,
    0x00,
    B01000000,
    B00000100,
    B00000001
};
const uint8_t Bitmaps::rain[] =
{
    0x00,
    B00100000,
    0x00,
    B01000000,
    0x00,
    B00100000,
    B00010000,
    B00001000
};
const uint8_t Bitmaps::wind[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00001000,
    B00001101,
    0x00
};
const uint8_t Bitmaps::cloudy[] =
{
    0x00,
    0x00,
    00010000,
    0x00,
    B00010000,
    B00001110,
    0x00,
    0x00
};
const uint8_t Bitmaps::lightning[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B00000100,
    B00000010,
    B00001000,
    B11000000
};
const uint8_t Bitmaps::low[] =
{
    0x00,
    0x00,
    0x00,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
};
const uint8_t Bitmaps::much[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B01110000,
    B00000010,
    0x00,
    0x00
};

// status
const uint8_t Bitmaps::run[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B00001000,
    0x00,
    0x00,
    B00000011
};
const uint8_t Bitmaps::net[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B00000001,
    0x00,
    B00010000,
    B10000000
};
const uint8_t Bitmaps::_time[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00010000,
    B00011000,
    B10000000
};
const uint8_t Bitmaps::ach[] =
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
const uint8_t Bitmaps::ach2[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    B10000000,
    B10000000,
    B10000000,
    0x00
};

const bitmap *Bitmaps::numbers[] = {
  &Bitmaps::zero,
  &Bitmaps::one,
  &Bitmaps::two,
  &Bitmaps::three,
  &Bitmaps::four,
  &Bitmaps::five,
  &Bitmaps::six,
  &Bitmaps::seven,
  &Bitmaps::eight,
  &Bitmaps::nine,
  &Bitmaps::ten,
  &Bitmaps::eleven,
  &Bitmaps::twelve
};
