#include <Wire.h>
#include <RtcDS3231.h>
// #include <LedControl.h>

#include "ClockDisplay.h"

#define CS_HOUR 2
#define CS_MINUTE16 1
#define CS_MINUTE1 0

RtcDS3231<TwoWire> rtc(Wire);
ClockDisplay disp = ClockDisplay(12, 11, 10);

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

    disp.begin();

    Serial.println("setup done");
}


// delay time between faces
unsigned long delaytime=1000;

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

    disp.showDigit(CS_MINUTE1, min1);
    disp.showDigit(CS_MINUTE16, min16);
    disp.showDigit(CS_HOUR, hour);

    delay(500);
}
