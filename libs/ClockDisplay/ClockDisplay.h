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
        void showClockDigit(uint8_t pos, uint8_t digit);
        void showCharacter(uint8_t pos, wchar_t c);
        void clear(uint8_t pos);
        void showTransition(uint8_t pos, uint8_t index, uint8_t nextDigit);
        void showCharTransition(uint8_t pos, uint8_t index, wchar_t next);
        void brighten();
        void dim();
        void shutdown();
        void startup();
        static wchar_t digitToChar(uint8_t pos, uint8_t d);
    private:
        uint8_t _getCharRow(wchar_t c, uint8_t row);
        void _updateBrightness();
        
        LedControl * _ledctrl;
        int8_t _brightness;
        bool _isShutdown;

        wchar_t * _currentDisplay;

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
        static const PROGMEM uint8_t c_firstquarter[];
        static const PROGMEM uint8_t c_secondquarter[];
        static const PROGMEM uint8_t c_thirdquarter[];
        static const PROGMEM uint8_t c_fourthquarter[];
        static const PROGMEM uint8_t c_hyphen[];
        static const PROGMEM uint8_t c_plus[];
        static const PROGMEM uint8_t c_twelveoclock_am[];
        static const PROGMEM uint8_t c_oneoclock_am[];
        static const PROGMEM uint8_t c_twooclock_am[];
        static const PROGMEM uint8_t c_threeoclock_am[];
        static const PROGMEM uint8_t c_fouroclock_am[];
        static const PROGMEM uint8_t c_fiveoclock_am[];
        static const PROGMEM uint8_t c_sixoclock_am[];
        static const PROGMEM uint8_t c_sevenoclock_am[];
        static const PROGMEM uint8_t c_eightoclock_am[];
        static const PROGMEM uint8_t c_nineoclock_am[];
        static const PROGMEM uint8_t c_tenoclock_am[];
        static const PROGMEM uint8_t c_elevenoclock_am[];
        static const PROGMEM uint8_t c_twelveoclock_pm[];
        static const PROGMEM uint8_t c_oneoclock_pm[];
        static const PROGMEM uint8_t c_twooclock_pm[];
        static const PROGMEM uint8_t c_threeoclock_pm[];
        static const PROGMEM uint8_t c_fouroclock_pm[];
        static const PROGMEM uint8_t c_fiveoclock_pm[];
        static const PROGMEM uint8_t c_sixoclock_pm[];
        static const PROGMEM uint8_t c_sevenoclock_pm[];
        static const PROGMEM uint8_t c_eightoclock_pm[];
        static const PROGMEM uint8_t c_nineoclock_pm[];
        static const PROGMEM uint8_t c_tenoclock_pm[];
        static const PROGMEM uint8_t c_elevenoclock_pm[];
};