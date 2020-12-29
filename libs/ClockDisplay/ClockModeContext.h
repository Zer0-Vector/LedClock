#pragma once

class ClockMode;

class ClockModeContext {
    public:
        ClockModeContext();
        ~ClockModeContext();
        ClockMode * getMode();
        static ClockMode * const cmShowTime;
        static ClockMode * const cmShowTemp;
    private:
        friend class ClockMode;
        ClockMode * _mode;
};