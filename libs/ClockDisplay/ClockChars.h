#pragma once
#include "ClockDisplay.h"
#include <avr/pgmspace.h>

const PROGMEM uint8_t ClockDisplay::c_zero[] = {
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_one[8] = {
    B00011000,
    B00111000,
    B01011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110
};

const PROGMEM uint8_t ClockDisplay::c_two[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111110
};

const PROGMEM uint8_t ClockDisplay::c_three[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00011100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_four[8] = {
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111110,
    B00000100,
    B00000100,
    B00000100
};

const PROGMEM uint8_t ClockDisplay::c_five[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_six[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_seven[8] = {
    B01111110,
    B01000010,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B01000000
};

const PROGMEM uint8_t ClockDisplay::c_eight[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_nine[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B00000100,
    B00001000,
    B00010000,
    B00100000
};

const PROGMEM uint8_t ClockDisplay::c_ten[8] = {
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010
};

const PROGMEM uint8_t ClockDisplay::c_eleven[8] = {
    B01111100,
    B01000010,
    B01000010,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B01111100
};

const PROGMEM uint8_t ClockDisplay::c_twelve[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_thirteen[8] = {
    B01111000,
    B01000100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000100,
    B01111000
};

const PROGMEM uint8_t ClockDisplay::c_fourteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01111110
};

const PROGMEM uint8_t ClockDisplay::c_fifteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01000000
};

// G
const PROGMEM uint8_t ClockDisplay::c_sixteen[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01000000,
    B01011110,
    B01000010,
    B01000010,
    B00111100
};

// H
const PROGMEM uint8_t ClockDisplay::c_seventeen[8] = {
    B01000010,
    B01000010,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B01000010
};

// I
const PROGMEM uint8_t ClockDisplay::c_eighteen[8] = {
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110
};

// J
const PROGMEM uint8_t ClockDisplay::c_nineteen[8] = {
    B00111110,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B00000100,
    B01000100,
    B00111000
};

// K
const PROGMEM uint8_t ClockDisplay::c_twenty[8] = {
    B01000010,
    B01000100,
    B01001000,
    B01110000,
    B01110000,
    B01001000,
    B01000100,
    B01000010
};

// L
const PROGMEM uint8_t ClockDisplay::c_twentyone[8] = {
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01111110
};

// M
const PROGMEM uint8_t ClockDisplay::c_twentytwo[8] = {
    B01000010,
    B01100110,
    B01100110,
    B01011010,
    B01000010,
    B01000010,
    B01000010,
    B01000010
};

// N
const PROGMEM uint8_t ClockDisplay::c_twentythree[8] = {
    B01000010,
    B01100010,
    B01100010,
    B01010010,
    B01001010,
    B01000110,
    B01000110,
    B01000010
};

// T
const PROGMEM uint8_t ClockDisplay::c_T[8] = {
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000
};

// ' '
const PROGMEM uint8_t ClockDisplay::c_blank[8] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
};

const PROGMEM uint8_t ClockDisplay::c_firstquarter[8] = {
    B00111100,
    B01001110,
    B10001111,
    B10001111,
    B10000001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_secondquarter[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10000001,
    B10001111,
    B10001111,
    B01001110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_thirdquarter[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10000001,
    B11110001,
    B11110001,
    B01110010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_fourthquarter[8] = {
    B00111100,
    B01110010,
    B11110001,
    B11110001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_hyphen[8] = {
    B00000000,
    B00000000,
    B00000000,
    B01111100,
    B00000000,
    B00000000,
    B00000000,
    B00000000
};

const PROGMEM uint8_t ClockDisplay::c_plus[8] = {
    B00000000,
    B00010000,
    B00010000,
    B01111100,
    B00010000,
    B00010000,
    B00000000,
    B00000000
};

const PROGMEM uint8_t ClockDisplay::c_twelveoclock_am[8] = {
    B00111100,
    B01011010,
    B10011001,
    B10011001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_oneoclock_am[8] = {
    B00111100,
    B01001110,
    B10011001,
    B10011001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_twooclock_am[8] = {
    B00111100,
    B01000010,
    B10000011,
    B10001111,
    B10001101,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_threeoclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10001111,
    B10001111,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_fouroclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10001101,
    B10001111,
    B10000011,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_fiveoclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10000001,
    B10011001,
    B10011001,
    B01001110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_sixoclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10000001,
    B10011001,
    B10011001,
    B01011010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_sevenoclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10000001,
    B10011001,
    B10011001,
    B01110010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_eightoclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B10110001,
    B11110001,
    B11000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_nineoclock_am[8] = {
    B00111100,
    B01000010,
    B10000001,
    B11110001,
    B11110001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_tenoclock_am[8] = {
    B00111100,
    B01000010,
    B11000001,
    B11110001,
    B10110001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_elevenoclock_am[8] = {
    B00111100,
    B01110010,
    B10011001,
    B10011001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_twelveoclock_pm[8] = {
    B00111100,
    B01100110,
    B11100111,
    B11100111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_oneoclock_pm[8] = {
    B00111100,
    B01110010,
    B11100111,
    B11100111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_twooclock_pm[8] = {
    B00111100,
    B01111110,
    B11111101,
    B11110001,
    B11110011,
    B11111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_threeoclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11110001,
    B11110001,
    B11111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_fouroclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11110011,
    B11110001,
    B11111101,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_fiveoclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11100111,
    B11100111,
    B01110010,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_sixoclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11100111,
    B11100111,
    B01100110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_sevenoclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11100111,
    B11100111,
    B01001110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_eightoclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11001111,
    B10001111,
    B10111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_nineoclock_pm[8] = {
    B00111100,
    B01111110,
    B11111111,
    B10001111,
    B10001111,
    B11111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_tenoclock_pm[8] = {
    B00111100,
    B01111110,
    B10111111,
    B10001111,
    B11001111,
    B11111111,
    B01111110,
    B00111100
};

const PROGMEM uint8_t ClockDisplay::c_elevenoclock_pm[8] = {
    B00111100,
    B01001110,
    B11100111,
    B11100111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
};
