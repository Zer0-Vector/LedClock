#pragma once

#include <Arduino.h>
#include <LedControl.h>

#define CS_HOUR 2
#define CS_MINUTE15 1
#define CS_MINUTE1 0

class ClockDisplay {
    public:
        ClockDisplay(int dataPin, int clockPin, int csPin);
        ~ClockDisplay();
        void begin();
        void showDigit(uint8_t pos, uint8_t digit);
        void showCharacter(uint8_t pos, char c);
        void clear(uint8_t pos);
        void showTransition(uint8_t pos, uint8_t index, uint8_t nextDigit);
        void showCharTransition(uint8_t pos, uint8_t index, char next);
        void brighten();
        void dim();
        static char digitToChar(uint8_t d);
    private:
        uint8_t _getCharRow(char c, uint8_t row);
        void _updateBrightness();
        
        LedControl * _ledctrl;
        uint8_t _brightness;

        char * _currentDisplay;

        static const PROGMEM uint8_t c_zero[];
        static const PROGMEM uint8_t c_one[];
        static const PROGMEM uint8_t c_two[];
        static const PROGMEM uint8_t c_three[];
        static const PROGMEM uint8_t c_four[];
        static const PROGMEM uint8_t c_five[];
        static const PROGMEM uint8_t c_six[];
        static const PROGMEM uint8_t c_seven[];
        static const PROGMEM uint8_t c_eight[];
        static const PROGMEM uint8_t c_nine[];
        static const PROGMEM uint8_t c_ten[];
        static const PROGMEM uint8_t c_eleven[];
        static const PROGMEM uint8_t c_twelve[];
        static const PROGMEM uint8_t c_thirteen[];
        static const PROGMEM uint8_t c_fourteen[];
        static const PROGMEM uint8_t c_fifteen[];
        static const PROGMEM uint8_t c_sixteen[];
        static const PROGMEM uint8_t c_seventeen[];
        static const PROGMEM uint8_t c_eighteen[];
        static const PROGMEM uint8_t c_nineteen[];
        static const PROGMEM uint8_t c_twenty[];
        static const PROGMEM uint8_t c_twentyone[];
        static const PROGMEM uint8_t c_twentytwo[];
        static const PROGMEM uint8_t c_twentythree[];
        static const PROGMEM uint8_t c_T[];
        static const PROGMEM uint8_t c_blank[];
};