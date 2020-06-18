#define WORDS_VORN 0
#define WORDS_NACHT 1
#define WORDS_ACH 2
#define WORDS_NEU 3
#define WORDS_HA 4
#define WORDS_WEIN 5
#define WORDS_ACHACH 6
#define WORDS_NIE 7
#define WORDS_NET 8
#define WORDS_REIN 9
#define WORDS_DRIN 10
#define WORDS_ZEIT 11
#define WORDS_EIN 12
#define WORDS_ECHT 13
#define WORDS_SEICHT 14
#define WORDS_EHE 15
#define WORDS_HAHN 16
#define WORDS_ICH 17
#define WORDS_DU 18
#define WORDS_ER 19
#define WORDS_SIE 20
#define WORDS_ES 21
#define WORDS_WIR 22
#define WORDS_IHR 23
#define WORDS_NA 24
#define WORDS_ROEHR 25
#define WORDS_HE 26
#define WORDS_HEHE 27
#define WORDS_SENSE 28
#define WORDS_HORN 29
#define WORDS_ZAHN 30
#define WORDS_ZAEHNE 31
#define WORDS_AHNE 32
#define WORDS_SIEH 33
#define WORDS_SEI 34
#define WORDS_FEIN 35
#define WORDS_WÖLFE 36
#define WORDS_SACHT 37
const uint8_t words[][8] PROGMEM {
  // vorn
  {
    0x00,
    B11110000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // Nacht
  {
    0x00,
    B00011111,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // ach
  {
    0x00,
    B00001110,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // neu
  {
    0x00,
    0x00,
    0x00,
    B00011100,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // ha
  {
    0x00,
    0x00,
    B11000000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // Wein
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B00000111,
    B00001000,
    0x00,
    0x00
  },
  // ach, ach
  {
    0x00,
    B00001110,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B11100000
  },
  // nie
  {
    0x00,
    B00010000,
    B00001100,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // NET
  {
    0x00,
    B00000001,
    B00000100,
    B00010000,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // rein
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B00001111,
    0x00,
    0x00,
    0x00
  },
  // drin
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B00011011,
    0x00,
    0x00,
    0x00
  },
  // Zeit
  {
    0x00,
    0x00,
    0x00,
    B10000000,
    0x00,
    B01000000,
    B01000000,
    B00010000
  },
  // ein
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B00000111,
    0x00,
    0x00,
    0x00
  },
  // echt
  {
    B00000100,
    B00000111,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // seicht
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B10000000,
    B01000000,
    B01000000,
    B01110000
  },
  // nicht
  {
    0x00,
    B00010111,
    B00001000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // ehe
  {
    0x00,
    0x00,
    B01100000,
    B00100000,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // Hahn
  {
    0x00,
    B11000000,
    B00110000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // ich
  {
    B00000010,
    B00000100,
    B00001000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // du
  {
    0x00,
    0x00,
    0x00,
    B00000100,
    B00010000,
    0x00,
    0x00,
    0x00
  },
  // er
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00000011
  },
  // sie
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B11100000,
    0x00,
    0x00,
    0x00
  },
  // es
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00000001,
    B00000010
  },
  // wir
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00001000,
    0x00,
    B00000101
  },
  // ihr
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00000010,
    B00000101
  },
  // na
  {
    0x00,
    B00011000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // röhr
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B00001000,
    B00000100,
    B00000010,
    B00000001
  },
  // he
  {
    0x00,
    0x00,
    B10000000,
    B01000000,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // hehe
  {
    0x00,
    0x00,
    B10000000,
    B01100000,
    B00100000,
    0x00,
    0x00,
    0x00
  },
  // Sense
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B11000000,
    B00111000,
    0x00,
    0x00
  },
  // Horn
  {
    0x00,
    B01110000,
    B10000000,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // Zahn
  {
    0x00,
    0x00,
    B01000000,
    B10110000,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // Zähne
  {
    0x00,
    0x00,
    B01000000,
    B11111000,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // ahne
  {
    0x00,
    0x00,
    B01000000,
    B00111000,
    0x00,
    0x00,
    0x00,
    0x00
  },
  // sieh
  {
    0x00,
    0x00,
    0x00,
    B00100000,
    B11100000,
    0x00,
    0x00,
    0x00
  },
  // sei
  {
    0x00,
    0x00,
    0x00,
    0x00,
    B10000000,
    B01000000,
    B01000000,
    0x00
  },
  // fein
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00000001,
    B11100000,
    0x00
  },
  // Wölfe
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00001111,
    B10000000,
    0x00
  },
  // sacht
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    B00000001,
    B11110000
  },
  // 
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
};
