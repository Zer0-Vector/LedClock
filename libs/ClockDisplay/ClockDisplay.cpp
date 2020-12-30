#include "ClockDisplay.h"
#include "ClockChars.h"
#include <avr/pgmspace.h>

ClockDisplay::ClockDisplay(int dataPin, int clockPin, int csPin) {
    _ledctrl = new LedControl(dataPin, clockPin, csPin, 3);
    _brightness = 0;
    _currentDisplay = (char*)calloc(3, sizeof(char));
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

    _ledctrl->shutdown(CS_HOUR, true);
    _ledctrl->shutdown(CS_MINUTE15, true);
    _ledctrl->shutdown(CS_MINUTE1, true);
    delay(1000);
    _ledctrl->shutdown(CS_HOUR, false);
    _ledctrl->shutdown(CS_MINUTE15, false);
    _ledctrl->shutdown(CS_MINUTE1, false);

    _updateBrightness();

    clear(CS_HOUR);
    clear(CS_MINUTE15);
    clear(CS_MINUTE1);
}

void ClockDisplay::_updateBrightness() {
    _ledctrl->setIntensity(CS_HOUR, _brightness);
    _ledctrl->setIntensity(CS_MINUTE15, _brightness);
    _ledctrl->setIntensity(CS_MINUTE1, _brightness);
}

void ClockDisplay::showDigit(uint8_t pos, uint8_t digit) {
    showCharacter(pos, digitToChar(digit));
}

char ClockDisplay::digitToChar(uint8_t d) {
    if (d < 10) {
        return '0' + d;
    } else {
        return 'A' + (d - 10);
    }
}

void ClockDisplay::showCharacter(uint8_t pos, char c) {
    for (int i = 0; i < 8; i++) {
        _ledctrl->setRow(pos, i, _getCharRow(c, i));
    }
    _currentDisplay[pos] = c;
}

void ClockDisplay::showTransition(uint8_t pos, uint8_t index, uint8_t nextDigit) {
    showCharTransition(pos, index, digitToChar(nextDigit));
}

void ClockDisplay::showCharTransition(uint8_t pos, uint8_t index, char next) {
    for (int i = 0; i < 8; i++) {
        _ledctrl->setRow(pos, i, index < i 
            ? _getCharRow(_currentDisplay[pos], i - 1 - index) 
            : _getCharRow(next, 8 - index + i)
            );
    }
}

uint8_t ClockDisplay::_getCharRow(char c, uint8_t row) {
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
    }
}