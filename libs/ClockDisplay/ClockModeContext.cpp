#include "ClockModeContext.h"
#include "ClockMode.h"

#include "CMShowTemp.h"
#include "CMShowTime.h"

ClockMode * const ClockModeContext::cmShowTime = new CMShowTime();
ClockMode * const ClockModeContext::cmShowTemp = new CMShowTemp();

ClockModeContext::ClockModeContext() {
    _mode = cmShowTime;
}

ClockMode * ClockModeContext::getMode() {
    return _mode;
}

