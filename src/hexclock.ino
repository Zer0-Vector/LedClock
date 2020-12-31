#include <Wire.h>
#include <RtcDS3231.h>

#include "ClockDisplay.h"

static RtcDS3231<TwoWire> rtc = RtcDS3231<TwoWire>(Wire);
static ClockDisplay disp = ClockDisplay(12, 11, 10);
static uint8_t lastHour = 0;
static uint8_t lastMinute = 0;

#define PIN_TEMP 2
#define PIN_SET 3
#define PIN_PLUS 4
#define PIN_MINUS 5
#define PIN_ALWAYSON 6

enum ClockState {
    SHOW_TIME,
    SHOW_TEMP,
    SET_HOUR,
    SET_MINUTE,
    SET_ALARM_HOUR,
    SET_ALARM_MINUTE,
    INVALID_TIME,
    HIDDEN_TIME,
} state;

void setup() {
    pinMode(PIN_TEMP, INPUT);
    pinMode(PIN_SET, INPUT);
    pinMode(PIN_PLUS, INPUT);
    pinMode(PIN_MINUS, INPUT);
    pinMode(PIN_ALWAYSON, INPUT);

    // unused pins
    pinMode(0, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
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
    if (!rtc.IsDateTimeValid()) {
        state = INVALID_TIME;
        Serial.println(F("Invalid date/time"));
        if (rtc.LastError() != 0) {
            Serial.print(F("RTC Error: "));
            Serial.println(rtc.LastError());
            for(;;);
        }
    } else {
        state = SHOW_TIME;
    }

    if (!rtc.GetIsRunning()) {
        rtc.SetIsRunning(true);
    }

    rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
    rtc.Enable32kHzPin(false);

    disp.begin();

    RtcDateTime now = rtc.GetDateTime();
    lastHour = now.Hour();
    lastMinute = now.Minute();

    Serial.println(F("setup done"));
    Serial.end();
}

static bool hourTrans = false;
static bool min16Trans = false;
static bool min1Trans = false;
static uint16_t transIndex = 8;

#define DISPLAY_TIMEOUT 5000
#define TIME_UPDATE_DELAY 75

void loop() {
    static bool tempDown = false;
    static bool setDown = false;
    static bool setHeld = false;

    static int8_t settingHour = 0;
    static int8_t settingMinute = 60;

    static unsigned long lastBlink = millis();
    static bool blinkOn = true;

    static unsigned long lastShowTime = millis();
    static bool showedTime = true;

    
    bool ppressed = scanForPlus();
    bool mpressed = scanForMinus();

    bool reading = digitalRead(PIN_TEMP) == HIGH;
    if (reading == tempDown && tempDown && (state == SHOW_TIME || state == HIDDEN_TIME)) {
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
            Serial.println(F("setUp!"));
            switch (state) {
                case INVALID_TIME:
                case SHOW_TIME:
                case HIDDEN_TIME:
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
                    if (settingHour > 23) {
                        settingHour = 0;
                    }
                } else if (scanForMinus()) {
                    settingHour--;
                    if (settingHour < 0) {
                        settingHour = 23;
                    }
                }
                break;
            case SET_MINUTE:
                if (ppressed) {
                    settingMinute++;
                    if (settingMinute == 60) {
                        settingMinute = 0;
                    }
                } else if (mpressed) {
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
        case INVALID_TIME:
            if (!blinkOn) {
                disp.clear(CS_HOUR);
                disp.clear(CS_MINUTE15);
                disp.clear(CS_MINUTE1);
            } else {
                showTime();
            }
            if (millis() - lastBlink > 250) {
                lastBlink = millis();
                blinkOn = !blinkOn;
            }
            break;
        case SHOW_TEMP:
            showTemp();
            break;
        case SET_HOUR:
            disp.showDigit(CS_MINUTE15, (settingMinute / 15));
            disp.showDigit(CS_MINUTE1, (settingMinute % 15));
            if (blinkOn) {
                disp.showDigit(CS_HOUR, settingHour);
            } else {
                disp.clear(CS_HOUR);
            }
            if (millis() - lastBlink > 250) {
                lastBlink = millis();
                blinkOn = !blinkOn;
            }
            break;
        case SET_MINUTE:
            disp.showDigit(CS_HOUR, settingHour);
            if (blinkOn) {
                disp.showDigit(CS_MINUTE15, settingMinute / 15);
                disp.showDigit(CS_MINUTE1, settingMinute % 15);
            } else {
                disp.clear(CS_MINUTE15);
                disp.clear(CS_MINUTE1);
            }
            if (millis() - lastBlink > 250) {
                lastBlink = millis();
                blinkOn = !blinkOn;
            }
            break;
        case SHOW_TIME:
            if (ppressed) {
                disp.brighten();
            }
            if (mpressed) {
                disp.dim();
            }
        default:
            reading = digitalRead(PIN_ALWAYSON) == HIGH;
            Serial.print("alwayson = ");
            Serial.println(reading);
            Serial.println(millis() - lastShowTime);
            if (ppressed || mpressed) {
                state = SHOW_TIME;
                showedTime = false;
            }
            if (reading || state != HIDDEN_TIME) {
                showTime();
                if (!showedTime || reading) {
                    lastShowTime = millis();
                    showedTime = true;
                }
                if (millis() - lastShowTime > DISPLAY_TIMEOUT) {
                    state = HIDDEN_TIME;
                }
            } else {
                disp.clear(CS_HOUR);
                disp.clear(CS_MINUTE15);
                disp.clear(CS_MINUTE1);
            }
    }
    showedTime = state == SHOW_TIME;
    delay(25);
}

void saveSetTime(uint8_t h, uint8_t m) {
    const RtcDateTime now = rtc.GetDateTime();
    const RtcDateTime set = RtcDateTime(now.Year(), now.Month(), now.Day(), h, m, 0);
    rtc.SetDateTime(set);
}

bool scanForPlus() {
    static bool plusDown = false;
    static bool plusHeld = false;
    bool reading = digitalRead(PIN_PLUS) == HIGH;
    bool rval = false;
    if (reading == plusDown && plusDown) {
        plusHeld = true;
    } else if (reading == plusDown && !plusDown) {
        if (plusHeld) {
            plusHeld = false;
            rval = true;
        }
    }
    plusDown = reading;
    return rval;
}

bool scanForMinus() {
    static bool minusDown = false;
    static bool minusHeld = false;
    bool reading = digitalRead(PIN_MINUS) == HIGH;
    bool rval = false;
    if (reading == minusDown && minusDown) {
        minusHeld = true;
    } else if (reading == minusDown && !minusDown) {
        if (minusHeld) {
            minusHeld = false;
            rval = true;
        }
    }
    minusDown = reading;
    return rval;
}

void showTemp() {
    RtcTemperature temp = rtc.GetTemperature();
    int tinf = (int)temp.AsFloatDegF();
    // TODO impose display limits: t<=-10 -> "T-L", t>100 -> "T+H"
    // TODO alter ClockDisplay to showCharacter in addition to showDigit

    // in base 10
    disp.showCharacter(CS_HOUR, 'T');
    disp.showDigit(CS_MINUTE15, tinf / 10);
    disp.showDigit(CS_MINUTE1, tinf % 10);
}

void showTime() {
    static unsigned long lastTimeUpdate = 0;
    if (millis() - lastTimeUpdate < TIME_UPDATE_DELAY) {
        return;
    }
    lastTimeUpdate = millis();
    RtcDateTime now = rtc.GetDateTime();
    uint8_t hour = now.Hour() % 24;
    uint8_t minute = now.Minute();

    if (transIndex >= 8) {
        min1Trans = false;
        min16Trans = false;
        hourTrans = false;
    }

    if (minute != lastMinute) {
        min1Trans = true;
        min16Trans = (minute / 15) != (lastMinute / 15);
        hourTrans = hour != lastHour;
        transIndex = 0;
    }

    uint8_t min15 = (minute / 15);
    uint8_t min1 = minute % 15;

    if (min1Trans) {
        disp.showTransition(CS_MINUTE1, transIndex, min1);
    } else {
        disp.showDigit(CS_MINUTE1, min1);
    }

    if (min16Trans) {
        disp.showTransition(CS_MINUTE15, transIndex, min15);
    } else {
        disp.showDigit(CS_MINUTE15, min15);
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
