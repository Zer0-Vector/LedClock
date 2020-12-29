#pragma once

#include "ClockMode.h"
#include "ClockDisplay.h"
#include <Wire.h>
#include <RtcDS3231.h>

class CMShowTime : public ClockMode {
    public:
        void display(ClockDisplay display, RtcDS3231<TwoWire> rtc);
        void tempDown(ClockModeContext * ctx);
};