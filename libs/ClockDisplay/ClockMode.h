#pragma once
#include "ClockDisplay.h"
#include "ClockModeContext.h"
#include <Wire.h>
#include <RtcDS3231.h>

class ClockMode {
    public:
        virtual void display(ClockDisplay display, RtcDS3231<TwoWire> rtc) = 0;
        virtual void plus(ClockModeContext * ctx);
        virtual void minus(ClockModeContext * ctx);
        virtual void setTime(ClockModeContext * ctx);
        virtual void alarm(ClockModeContext * ctx);
        virtual void tempDown(ClockModeContext * ctx);
        virtual void tempUp(ClockModeContext * ctx);
    protected:
        void setMode(ClockModeContext * ctx, ClockMode * mode);
};