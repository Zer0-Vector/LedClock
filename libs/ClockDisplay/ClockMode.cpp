#include "ClockMode.h"
#include "ClockModeContext.h"

void ClockMode::plus(ClockModeContext * ctx) { }
void ClockMode::minus(ClockModeContext * ctx) { }
void ClockMode::setTime(ClockModeContext * ctx) { }
void ClockMode::alarm(ClockModeContext * ctx) { }
void ClockMode::tempUp(ClockModeContext * ctx) { }
void ClockMode::tempDown(ClockModeContext * ctx) { }

void ClockMode::setMode(ClockModeContext * ctx, ClockMode * mode) {
    ctx->_mode = mode;
}