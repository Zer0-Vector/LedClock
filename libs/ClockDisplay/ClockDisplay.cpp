#include "ClockDisplay.h"
#include "ClockChars.h"

ClockDisplay::ClockDisplay(int dataPin, int clockPin, int csPin) {
    _ledctrl = new LedControl(dataPin, clockPin, csPin, 3);
}

ClockDisplay::~ClockDisplay() {
    delete _ledctrl;
}

void ClockDisplay::begin() {
    _ledctrl->clearDisplay(0);
    _ledctrl->clearDisplay(1);
    _ledctrl->clearDisplay(2);

    _ledctrl->shutdown(0, true);
    _ledctrl->shutdown(1, true);
    _ledctrl->shutdown(2, true);
    delay(1000);
    _ledctrl->shutdown(0, false);
    _ledctrl->shutdown(1, false);
    _ledctrl->shutdown(2, false);

    _ledctrl->setIntensity(0, 0);
    _ledctrl->setIntensity(1, 0);
    _ledctrl->setIntensity(2, 0);

    _ledctrl->clearDisplay(0);
    _ledctrl->clearDisplay(1);
    _ledctrl->clearDisplay(2);
}

void ClockDisplay::showDigit(uint8_t pos, uint8_t digit) {
    const uint8_t * pixels = _getDigitMatrix(digit);
    _ledctrl->setRow(pos, 0, pixels[0]);
    _ledctrl->setRow(pos, 1, pixels[1]);
    _ledctrl->setRow(pos, 2, pixels[2]);
    _ledctrl->setRow(pos, 3, pixels[3]);
    _ledctrl->setRow(pos, 4, pixels[4]);
    _ledctrl->setRow(pos, 5, pixels[5]);
    _ledctrl->setRow(pos, 6, pixels[6]);
    _ledctrl->setRow(pos, 7, pixels[7]);
}

void ClockDisplay::showTransition(uint8_t pos, uint8_t index, uint8_t nextDigit, uint8_t currentDigit) {
    const uint8_t * nextPixels = _getDigitMatrix(nextDigit);
    const uint8_t * currentPixels = _getDigitMatrix(currentDigit);
    // index should be in [0,8)
    _ledctrl->setRow(pos, 0, nextPixels[7 - index]);
    _ledctrl->setRow(pos, 1, index < 1 ? currentPixels[0] : nextPixels[8 - index]);
    _ledctrl->setRow(pos, 2, index < 2 ? currentPixels[1 - index] : nextPixels[9 - index]);
    _ledctrl->setRow(pos, 3, index < 3 ? currentPixels[2 - index] : nextPixels[10 - index]);
    _ledctrl->setRow(pos, 4, index < 4 ? currentPixels[3 - index] : nextPixels[11 - index]);
    _ledctrl->setRow(pos, 5, index < 5 ? currentPixels[4 - index] : nextPixels[12 - index]);
    _ledctrl->setRow(pos, 6, index < 6 ? currentPixels[5 - index] : nextPixels[13 - index]);
    _ledctrl->setRow(pos, 7, index < 7 ? currentPixels[6 - index] : nextPixels[7]);
}

const uint8_t * ClockDisplay::_getDigitMatrix(uint8_t digit) {
    switch (digit) {
        case 0: return c_zero;
        case 1: return c_one;
        case 2: return c_two;
        case 3: return c_three;
        case 4: return c_four;
        case 5: return c_five;
        case 6: return c_six;
        case 7: return c_seven;
        case 8: return c_eight;
        case 9: return c_nine;
        case 10: return c_ten;
        case 11: return c_eleven;
        case 12: return c_twelve;
        case 13: return c_thirteen;
        case 14: return c_fourteen;
        case 15: return c_fifteen;
    }
}