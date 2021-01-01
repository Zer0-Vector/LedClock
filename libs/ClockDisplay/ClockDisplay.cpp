#include "ClockDisplay.h"
#include "ClockChars.h"
#include <avr/pgmspace.h>

ClockDisplay::ClockDisplay(int dataPin, int clockPin, int csPin) {
    _ledctrl = new LedControl(dataPin, clockPin, csPin, 3);
    _brightness = 0;
    _isShutdown = true;
    _currentDisplay = (wchar_t*)calloc(3, sizeof(wchar_t));
    _currentDisplay[CS_MINUTE1] = ' ';
    _currentDisplay[CS_MINUTE15] = ' ';
    _currentDisplay[CS_HOUR] = ' ';
}

ClockDisplay::~ClockDisplay() {
    free(_currentDisplay);
    delete _ledctrl;
}

void ClockDisplay::clear(uint8_t pos) {
    _ledctrl->clearDisplay(pos);
    _currentDisplay[pos] = ' ';
}

void ClockDisplay::brighten() {
    // increment and check upper limit
    if (++_brightness > 15) _brightness = 15;
    _updateBrightness();
}

void ClockDisplay::dim() {
    // decrement and check lower limit
    if (--_brightness < 0) _brightness = 0;
    _updateBrightness();
}

void ClockDisplay::begin() {
    _ledctrl->clearDisplay(CS_HOUR);
    _ledctrl->clearDisplay(CS_MINUTE15);
    _ledctrl->clearDisplay(CS_MINUTE1);

    shutdown();
    delay(1000);
    startup();

    _updateBrightness();

    clear(CS_HOUR);
    clear(CS_MINUTE15);
    clear(CS_MINUTE1);
}

void ClockDisplay::_updateBrightness() {
    if (_isShutdown) startup();
    _ledctrl->setIntensity(CS_HOUR, _brightness);
    _ledctrl->setIntensity(CS_MINUTE15, _brightness);
    _ledctrl->setIntensity(CS_MINUTE1, _brightness);
}

void ClockDisplay::showClockDigit(uint8_t pos, uint8_t digit) {
    if (_isShutdown) startup();
    showCharacter(pos, digitToChar(pos, digit));
}

wchar_t ClockDisplay::digitToChar(uint8_t pos, uint8_t d) {
    if (pos == CS_MINUTE15) {
        switch (d) {
            case 0:
                return L'╗';
            case 1:
                return L'╝';
            case 2:
                return L'╚';
            case 3:
                return L'╔';
        }
    }

    if (pos == CS_HOUR) {
        return 'a' + d;
    }

    if (d < 10) {
        return '0' + d;
    } else {
        return 'A' + (d - 10);
    }
}

void ClockDisplay::showCharacter(uint8_t pos, wchar_t c) {
    if (_isShutdown) startup();
    for (int i = 0; i < 8; i++) {
        _ledctrl->setRow(pos, i, _getCharRow(c, i));
    }
    _currentDisplay[pos] = c;
}

void ClockDisplay::showTransition(uint8_t pos, uint8_t index, uint8_t nextDigit) {
    if (_isShutdown) startup();
    showCharTransition(pos, index, digitToChar(pos, nextDigit));
}

void ClockDisplay::showCharTransition(uint8_t pos, uint8_t index, wchar_t next) {
    if (_isShutdown) startup();
    for (int i = 0; i < 8; i++) {
        _ledctrl->setRow(pos, i, index < i 
            ? _getCharRow(_currentDisplay[pos], i - 1 - index) 
            : _getCharRow(next, 8 - index + i)
            );
    }
}

void ClockDisplay::shutdown() {
    _ledctrl->shutdown(CS_HOUR, true);
    _ledctrl->shutdown(CS_MINUTE15, true);
    _ledctrl->shutdown(CS_MINUTE1, true);
    _isShutdown = true;
}

void ClockDisplay::startup() {
    _ledctrl->shutdown(CS_HOUR, false);
    _ledctrl->shutdown(CS_MINUTE15, false);
    _ledctrl->shutdown(CS_MINUTE1, false);
    _isShutdown = false;
}

uint8_t ClockDisplay::_getCharRow(wchar_t c, uint8_t row) {
    switch (c) {
        case ' ': return pgm_read_byte_near(c_blank + row);
        case '0': return pgm_read_byte_near(c_zero + row);
        case '1': return pgm_read_byte_near(c_one + row);
        case '2': return pgm_read_byte_near(c_two + row);
        case '3': return pgm_read_byte_near(c_three + row);
        case '4': return pgm_read_byte_near(c_four + row);
        case '5': return pgm_read_byte_near(c_five + row);
        case '6': return pgm_read_byte_near(c_six + row);
        case '7': return pgm_read_byte_near(c_seven + row);
        case '8': return pgm_read_byte_near(c_eight + row);
        case '9': return pgm_read_byte_near(c_nine + row);
        case 'A': return pgm_read_byte_near(c_ten + row);
        case 'B': return pgm_read_byte_near(c_eleven + row);
        case 'C': return pgm_read_byte_near(c_twelve + row);
        case 'D': return pgm_read_byte_near(c_thirteen + row);
        case 'E': return pgm_read_byte_near(c_fourteen + row);
        case 'F': return pgm_read_byte_near(c_fifteen + row);
        case 'G': return pgm_read_byte_near(c_sixteen + row);
        case 'H': return pgm_read_byte_near(c_seventeen + row);
        case 'I': return pgm_read_byte_near(c_eighteen + row);
        case 'J': return pgm_read_byte_near(c_nineteen + row);
        case 'K': return pgm_read_byte_near(c_twenty + row);
        case 'L': return pgm_read_byte_near(c_twentyone + row);
        case 'M': return pgm_read_byte_near(c_twentytwo + row);
        case 'N': return pgm_read_byte_near(c_twentythree + row);
        case 'T': return pgm_read_byte_near(c_T + row);
        case L'╗': return pgm_read_byte_near(c_firstquarter + row);
        case L'╝': return pgm_read_byte_near(c_secondquarter + row);
        case L'╚': return pgm_read_byte_near(c_thirdquarter + row);
        case L'╔': return pgm_read_byte_near(c_fourthquarter + row);
        case '-': return pgm_read_byte_near(c_hyphen + row);
        case '+': return pgm_read_byte_near(c_plus + row);
        case 'a': return pgm_read_byte_near(c_twelveoclock_am + row);
        case 'b': return pgm_read_byte_near(c_oneoclock_am + row);
        case 'c': return pgm_read_byte_near(c_twooclock_am + row);
        case 'd': return pgm_read_byte_near(c_threeoclock_am + row);
        case 'e': return pgm_read_byte_near(c_fouroclock_am + row);
        case 'f': return pgm_read_byte_near(c_fiveoclock_am + row);
        case 'g': return pgm_read_byte_near(c_sixoclock_am + row);
        case 'h': return pgm_read_byte_near(c_sevenoclock_am + row);
        case 'i': return pgm_read_byte_near(c_eightoclock_am + row);
        case 'j': return pgm_read_byte_near(c_nineoclock_am + row);
        case 'k': return pgm_read_byte_near(c_tenoclock_am + row);
        case 'l': return pgm_read_byte_near(c_elevenoclock_am + row);
        case 'm': return pgm_read_byte_near(c_twelveoclock_pm + row);
        case 'n': return pgm_read_byte_near(c_oneoclock_pm + row);
        case 'o': return pgm_read_byte_near(c_twooclock_pm + row);
        case 'p': return pgm_read_byte_near(c_threeoclock_pm + row);
        case 'q': return pgm_read_byte_near(c_fouroclock_pm + row);
        case 'r': return pgm_read_byte_near(c_fiveoclock_pm + row);
        case 's': return pgm_read_byte_near(c_sixoclock_pm + row);
        case 't': return pgm_read_byte_near(c_sevenoclock_pm + row);
        case 'u': return pgm_read_byte_near(c_eightoclock_pm + row);
        case 'v': return pgm_read_byte_near(c_nineoclock_pm + row);
        case 'w': return pgm_read_byte_near(c_tenoclock_pm + row);
        case 'x': return pgm_read_byte_near(c_elevenoclock_pm + row);
    }
}