#pragma once
#include <Debounced.h>
#include "ClockModeContext.h"


class ClockControlDriver {
    public:
        ClockControlDriver(uint8_t pinPlus, uint8_t pinMinus, uint8_t pinSetTime, uint8_t pinAlarm, uint8_t pinTemp);
        ~ClockControlDriver();
        void tick();
    private:
        Debounced _dPlus;
        Debounced _dMinus;
        Debounced _dSetTime;
        Debounced _dAlarm;
        Debounced _dTemp;

        uint8_t _pPlus;
        uint8_t _pMinus;
        uint8_t _pSetTime;
        uint8_t _pAlarm;
        uint8_t _pTemp;

        ClockModeContext * _ctx;
};