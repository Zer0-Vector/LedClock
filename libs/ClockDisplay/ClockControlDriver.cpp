#include <Arduino.h>
#include <Debounced.h>
#include "ClockControlDriver.h"
#include "ClockMode.h"

ClockControlDriver::ClockControlDriver(uint8_t pinPlus, uint8_t pinMinus, uint8_t pinSetTime, uint8_t pinAlarm, uint8_t pinTemp)
    : _pPlus(pinPlus), _pMinus(pinMinus), _pSetTime(pinSetTime), _pAlarm(pinAlarm), _pTemp(pinTemp)
{
    pinMode(_pPlus, INPUT);
    pinMode(_pMinus, INPUT);
    pinMode(_pSetTime, INPUT);
    pinMode(_pAlarm, INPUT);
    pinMode(_pTemp, INPUT);

    _dPlus = Debounced();
    _dMinus = Debounced();
    _dSetTime = Debounced();
    _dAlarm = Debounced();
    _dTemp = Debounced();

    _ctx = new ClockModeContext();
}

ClockControlDriver::~ClockControlDriver() {
    delete _ctx;
}

void ClockControlDriver::tick() {
    if (_dTemp.digitalRead(_pTemp)) {
        if (_dTemp.value() == HIGH) {
            _ctx->getMode()->tempDown(_ctx);
        } else {
            _ctx->getMode()->tempUp(_ctx);
        }
    }
}