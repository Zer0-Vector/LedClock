#include "CMShowTemp.h"
#include "ClockModeContext.h"
#include <Wire.h>
#include <RtcDS3231.h>
#include <RtcTemperature.h>

void CMShowTemp::display(ClockDisplay display, RtcDS3231<TwoWire> rtc) {
    RtcTemperature temp = rtc.GetTemperature();
    int tinf = (int)temp.AsFloatDegF();
    // TODO impose display limits: t<=-10 -> "T-L", t>100 -> "T+H"
    // TODO alter ClockDisplay to showCharacter in addition to showDigit

    // in base 10
    display.clear(CS_HOUR); // TODO display.showCharacter('T');
    display.showDigit(CS_MINUTE16, tinf / 10);
    display.showDigit(CS_MINUTE1, tinf % 10);
}

void CMShowTemp::tempUp(ClockModeContext * ctx) {
    setMode(ctx, ClockModeContext::cmShowTime);
}