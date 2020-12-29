#pragma once

#include <Arduino.h>
#include <LedControl.h>

#define CS_HOUR 2
#define CS_MINUTE16 1
#define CS_MINUTE1 0

class ClockDisplay {
    public:
        ClockDisplay(int dataPin, int clockPin, int csPin);
        ~ClockDisplay();
        void begin();
        void showDigit(uint8_t pos, uint8_t digit);
        void clear(uint8_t pos);
        void showTransition(uint8_t pos, uint8_t index, uint8_t nextDigit, uint8_t currentDigit);
        void brighten();
        void dim();
    private:
        const uint8_t * _getDigitMatrix(uint8_t digit);
        void _updateBrightness();
        
        LedControl * _ledctrl;
        uint8_t _brightness;

        static const uint8_t c_zero[];
        static const uint8_t c_one[];
        static const uint8_t c_two[];
        static const uint8_t c_three[];
        static const uint8_t c_four[];
        static const uint8_t c_five[];
        static const uint8_t c_six[];
        static const uint8_t c_seven[];
        static const uint8_t c_eight[];
        static const uint8_t c_nine[];
        static const uint8_t c_ten[];
        static const uint8_t c_eleven[];
        static const uint8_t c_twelve[];
        static const uint8_t c_thirteen[];
        static const uint8_t c_fourteen[];
        static const uint8_t c_fifteen[];
};