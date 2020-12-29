#include "CMShowTime.h"
#include "ClockMode.h"
#include "ClockDisplay.h"
#include <Wire.h>
#include <RtcDS3231.h>

void CMShowTime::display(ClockDisplay display, RtcDS3231<TwoWire> rtc) {
    // TODO
}

void CMShowTime::tempDown(ClockModeContext * ctx) {
    setMode(ctx, ClockModeContext::cmShowTemp);
}