#include <Wire.h>
#include <RtcDS3231.h>
#include <LedControl.h>

#define CS_HOUR 2
#define CS_MINUTE16 1
#define CS_MINUTE1 0

LedControl lc = LedControl(12,11,10,3);
RtcDS3231<TwoWire> rtc(Wire);

void setup() {
    // unused pins
    pinMode(0, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A6, INPUT_PULLUP);
    pinMode(A7, INPUT_PULLUP);

    Serial.begin(9600);

    rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Serial.println(__DATE__);
    Serial.println(__TIME__);
    if (!rtc.IsDateTimeValid()) {
        Serial.println("Invalid date/time");
        if (rtc.LastError() != 0) {
            Serial.println("RTC Error: "+String(rtc.LastError()));
            for(;;);
        } else {
            rtc.SetDateTime(compiled);
        }
    }
    if (!rtc.GetIsRunning()) {
        rtc.SetIsRunning(true);
    }

    if (rtc.GetDateTime() < compiled) {
        rtc.SetDateTime(compiled);
    }

    rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
    rtc.Enable32kHzPin(false);

    lc.shutdown(0, true);
    lc.shutdown(1, true);
    lc.shutdown(2, true);
    delay(1000);
    lc.shutdown(0, false);
    lc.shutdown(1, false);
    lc.shutdown(2, false);

    lc.setIntensity(0, 8);
    lc.setIntensity(1, 8);
    lc.setIntensity(2, 8);

    lc.clearDisplay(0);
    lc.clearDisplay(1);
    lc.clearDisplay(2);
    Serial.println("setup done");
}


// delay time between faces
unsigned long delaytime=1000;

uint8_t zero[8] = {
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

uint8_t one[8] = {
    B00011000,
    B00111000,
    B01011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110
};

uint8_t two[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111110
};

uint8_t three[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00011100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

uint8_t four[8] = {
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111110,
    B00000100,
    B00000100,
    B00000100
};

uint8_t five[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

uint8_t six[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

uint8_t seven[8] = {
    B01111110,
    B01000010,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B01000000
};

uint8_t eight[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

uint8_t nine[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B00000100,
    B00001000,
    B00010000,
    B00100000
};

uint8_t ten[8] = {
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010
};

uint8_t eleven[8] = {
    B01111100,
    B01000010,
    B01000010,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B01111100
};

uint8_t twelve[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000010,
    B00111100
};

uint8_t thirteen[8] = {
    B01111000,
    B01000100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000100,
    B01111000
};

uint8_t fourteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01111110
};

uint8_t fifteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01000000
};

void draw(int addr, uint8_t * pixels) {
    lc.setRow(addr,0,pixels[0]);
    lc.setRow(addr,1,pixels[1]);
    lc.setRow(addr,2,pixels[2]);
    lc.setRow(addr,3,pixels[3]);
    lc.setRow(addr,4,pixels[4]);
    lc.setRow(addr,5,pixels[5]);
    lc.setRow(addr,6,pixels[6]);
    lc.setRow(addr,7,pixels[7]);
}

static uint8_t hour2 = 12;
static uint8_t minute2 = 0;

void loop() {
    static unsigned long m = millis();

    static uint8_t * hourPixels;;
    static uint8_t * minute16Pixels;
    static uint8_t * minute1Pixels;
    
    RtcDateTime now = rtc.GetDateTime();
    Serial.println("now = " + String(now.Hour()) + ":" + String(now.Minute()));
    uint8_t hour = now.Hour() % 12;
    uint8_t minute = now.Minute();

    uint8_t min16 = (minute & 0xF0) >> 4;
    uint8_t min1 = minute & 0x0F;

    hourPixels = getDigit(hour);
    minute16Pixels = getDigit(min16);
    minute1Pixels = getDigit(min1);

    draw(CS_MINUTE1, minute1Pixels);
    draw(CS_MINUTE16, minute16Pixels);
    draw(CS_HOUR, hourPixels);

    delay(500);
}

uint8_t* getDigit(uint8_t digit) {
    switch (digit) {
        case 0: return zero;
        case 1: return one;
        case 2: return two;
        case 3: return three;
        case 4: return four;
        case 5: return five;
        case 6: return six;
        case 7: return seven;
        case 8: return eight;
        case 9: return nine;
        case 10: return ten;
        case 11: return eleven;
        case 12: return twelve;
        case 13: return thirteen;
        case 14: return fourteen;
        case 15: return fifteen;
    }
}
