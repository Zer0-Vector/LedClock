#include <Wire.h>
#include <RtcDS3231.h>

#include "ClockDisplay.h"

static RtcDS3231<TwoWire> rtc = RtcDS3231<TwoWire>(Wire);
static ClockDisplay disp = ClockDisplay(12, 11, 10);
static uint8_t lastHour = 12;
static uint8_t lastMinute = 0;

#define PIN_TEMP 2
#define PIN_SET 3
#define PIN_PLUS 4
#define PIN_MINUS 5

void setup() {
    pinMode(PIN_TEMP, INPUT);
    pinMode(PIN_SET, INPUT);
    pinMode(PIN_PLUS, INPUT_PULLUP);
    pinMode(PIN_MINUS, INPUT_PULLUP);

    // unused pins
    pinMode(0, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
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
        Serial.println(F("Invalid date/time"));
        if (rtc.LastError() != 0) {
            Serial.print(F("RTC Error: "));
            Serial.println(rtc.LastError());
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

    RtcDateTime now = rtc.GetDateTime();
    lastHour = now.Hour();
    lastMinute = now.Minute();

    Serial.println(F("setup done"));
    // Serial.end();
}

static bool hourTrans = false;
static bool min16Trans = false;
static bool min1Trans = false;
static uint16_t transIndex = 8;

enum ClockState {
    SHOW_TIME,
    SHOW_TEMP,
    SET_HOUR,
    SET_MINUTE,
    SET_ALARM_HOUR,
    SET_ALARM_MINUTE
} state;

void loop() {
    static bool tempDown = false;
    static bool setDown = false;
    static bool setHeld = false;
    static bool plusDown = false;
    static bool minusDown = false;

    static int8_t settingHour = 0;
    static int8_t settingMinute = 60;

    static unsigned long lastBlink = millis();
    static bool blinkOn = true;

    bool reading = digitalRead(PIN_TEMP) == HIGH;
    if (reading == tempDown && tempDown && state == SHOW_TIME) {
        state = SHOW_TEMP;
    } else if (reading == tempDown && !tempDown && state == SHOW_TEMP) {
        state = SHOW_TIME;
    }
    tempDown = reading;

    reading = digitalRead(PIN_SET) == HIGH;
    if (reading == setDown && setDown) {
        Serial.println(F("setDown"));
        setHeld = true;
    } else if (reading == setDown && !setDown) {
        if (setHeld) {
            // BUTTON PRESSED!
            Serial.println(F("setUp!"));
            switch (state) {
                case SHOW_TIME:
                    state = SET_HOUR;
                    settingHour = rtc.GetDateTime().Hour();
                    settingMinute = rtc.GetDateTime().Minute();
                    Serial.println(F("state=SET_HOUR"));
                    break;
                case SET_HOUR:
                    state = SET_MINUTE;
                    Serial.println(F("state=SET_MINUTE"));
                    break;
                case SET_MINUTE:
                    saveSetTime(settingHour, settingMinute);
                    state = SHOW_TIME;
                    Serial.println(F("state=SHOW_TIME"));
                    break;
            }
        }
        setHeld = false;
        switch (state) {
            case SET_HOUR:
                if (scanForPlus()) {
                    settingHour++;
                } else if (scanForMinus()) {
                    settingHour--;
                }
                break;
            case SET_MINUTE:
                if (scanForPlus()) {
                    settingMinute++;
                    if (settingMinute == 60) {
                        settingMinute = 0;
                    }
                } else if (scanForMinus()) {
                    settingMinute--;
                    if (settingMinute < 0) {
                        settingMinute = 59;
                    }
                }
                break;
        }
    }
    setDown = reading;

    switch (state) {
        case SHOW_TEMP:
            showTemp();
            break;
        case SET_HOUR:
        case SET_MINUTE:
            if (blinkOn) {
                disp.showDigit(CS_HOUR, settingHour);
                disp.showDigit(CS_MINUTE16, (settingMinute & 0xF0) >> 4);
                disp.showDigit(CS_MINUTE1, (settingMinute & 0x0F));
            } else {
                disp.clear(CS_HOUR);
                disp.clear(CS_MINUTE16);
                disp.clear(CS_MINUTE1);
            }
            if (millis() - lastBlink > 250) {
                lastBlink = millis();
                blinkOn = !blinkOn;
            }
            break;
        default:
            showTime();
            break;
    }
    delay(75);
}

void saveSetTime(uint8_t h, uint8_t m) {
    // TODO
}

bool scanForPlus() {
    return false; // TODO
}

bool scanForMinus() {
    return false; // TODO
}

void showTemp() {
    RtcTemperature temp = rtc.GetTemperature();
    int tinf = (int)temp.AsFloatDegF();
    // TODO impose display limits: t<=-10 -> "T-L", t>100 -> "T+H"
    // TODO alter ClockDisplay to showCharacter in addition to showDigit

    // in base 10
    disp.showCharacter(CS_HOUR, 'T');
    disp.showDigit(CS_MINUTE16, tinf / 10);
    disp.showDigit(CS_MINUTE1, tinf % 10);
}

void showTime() {
    RtcDateTime now = rtc.GetDateTime();
    uint8_t hour = now.Hour() % 12;
    if (hour == 0) {
        hour = 12;
    }
    uint8_t minute = now.Minute();

    if (transIndex >= 8) {
        min1Trans = false;
        min16Trans = false;
        hourTrans = false;
    }

    if (minute != lastMinute) {
        min1Trans = true;
        min16Trans = (minute & 0xF0) != (lastMinute & 0xF0);
        hourTrans = hour != lastHour;
        transIndex = 0;
    }

    uint8_t min16 = (minute & 0xF0) >> 4;
    uint8_t min1 = minute & 0x0F;

    if (min1Trans) {
        disp.showTransition(CS_MINUTE1, transIndex, min1);
    } else {
        disp.showDigit(CS_MINUTE1, min1);
    }

    if (min16Trans) {
        disp.showTransition(CS_MINUTE16, transIndex, min16);
    } else {
        disp.showDigit(CS_MINUTE16, min16);
    }
    
    if (hourTrans) {
        disp.showTransition(CS_HOUR, transIndex, hour);
    } else {
        disp.showDigit(CS_HOUR, hour);
    }
    transIndex++;
    lastMinute = minute;
    lastHour = hour;
}
