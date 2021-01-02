#include <Wire.h>
#include <RtcDS3231.h>

#include <ClockDisplay.h>

static RtcDS3231<TwoWire> rtc = RtcDS3231<TwoWire>(Wire);
static ClockDisplay disp = ClockDisplay(12, 11, 10);

#define PIN_TEMP 2
#define PIN_SET 3
#define PIN_PLUS 4
#define PIN_MINUS 5
#define PIN_ALWAYSON 6

enum ClockState {
    SHOW_TIME,
    SHOW_TEMP,
    SHOW_ALARM1,
    SHOW_ALARM2,
    SET_TIME,
    SET_HOUR, // when hold trigger happens, before button release
    SET_MINUTE,
    SET_ALARM1, // when hold trigger happens, before button release
    SET_ALARM1_HOUR,
    SET_ALARM1_MINUTE,
    SET_ALARM2, // when hold trigger happens, before button release
    SET_ALARM2_HOUR,
    SET_ALARM2_MINUTE,
    INVALID_TIME,
    HIDDEN_TIME,
} state;

enum ClockButton : uint8_t {
    PLUS = 0x01,
    MINUS = 0x02,
    SET = 0x04,
    ALARM1 = 0x08,
    ALARM2 = 0x10,
    TEMP = 0x20,
    SNOOZE = 0x40
};

enum AlarmState : uint8_t {
    SILENT = 0x00,
    ALARM1_ON = 0x01,
    ALARM2_ON = 0x02,
    ALARM1_SNOOZE = 0x10,
    ALARM2_SNOOZE = 0x20
} alarmSoundState;

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

    Serial.println(F("setup done"));
    // Serial.end();
}

static int8_t settingHour = 25;
static int8_t settingMinute = 60;

#define DISPLAY_TIMEOUT 5000
#define TIME_UPDATE_DELAY 75
#define TICK_DELAY 25
#define BUTTON_HOLD_TIMEOUT 2000
#define BLINK_DELAY 250
#define BLINK_DELAYx2 500


void loop() {
    static uint8_t buttonsDown = 0x00;

    uint8_t buttonsUp = queryButtonsState(&buttonsDown);
    uint8_t buttonsHoldTrigger = queryHoldState(buttonsDown);

    if (buttonsDown > 0) {
        triggerButtonsDown(buttonsDown);
    }
    if (buttonsUp > 0) {
        triggerButtonsPressed(buttonsUp);
    }
    if (buttonsHoldTrigger > 0) {
        triggerButtonsHeld(buttonsHoldTrigger);
    }

    updateDisplay();

    delay(TICK_DELAY);
}

/**
 * buttonsDown reflects what buttons are held down.
 * returns: buttonsUp is an event trigger when a button is released. It is non-zero for 1 tick.
 */
uint8_t queryButtonsState(uint8_t * buttonsDown) {
    static uint8_t lastReading = 0x00;
    uint8_t reading = 0x00;
    reading |= queryButton(PIN_PLUS, PLUS);
    reading |= queryButton(PIN_MINUS, MINUS);
    reading |= queryButton(PIN_SET, SET);
    reading |= queryButton(PIN_TEMP, TEMP);
    
    // reading |= queryButton(PIN_ALARM1, ALARM1);
    // reading |= queryButton(PIN_ALARM2, ALARM2);
    // reading |= queryButton(PIN_SNOOZE, SNOOZE);
    uint8_t rval = 0x00;
    for (uint16_t b = 1; b < 0x100; b <<= 1) {
        if ((reading & b) == (lastReading & b)) {
            if (reading & b) {
                *buttonsDown |= b;
            } else {
                rval |= *buttonsDown & b;
                *buttonsDown &= ~b;
            }
        }
    }
    lastReading = reading;
    return rval;
}

uint8_t queryHoldState(uint8_t buttonsDown) {
    static unsigned long setHoldTime = 0;
    static unsigned long alarm1HoldTime = 0;
    static unsigned long alarm2HoldTime = 0;
    static unsigned long plusHoldTime = 0;
    static unsigned long minusHoldtime = 0;

    uint8_t buttonsHeld = 0x00;
    if (holdingButtonTick(buttonsDown & ClockButton::SET, &setHoldTime)) {
        buttonsHeld |= ClockButton::SET;
    } else if (holdingButtonTick(buttonsDown & ClockButton::ALARM1, &alarm1HoldTime)) {
        buttonsHeld |= ClockButton::ALARM1;
    } else if (holdingButtonTick(buttonsDown & ClockButton::ALARM2, &alarm2HoldTime)) {
        buttonsHeld |= ClockButton::ALARM2;
    } else if (holdingButtonTick(buttonsDown & ClockButton::PLUS, &plusHoldTime)) {
        buttonsHeld |= ClockButton::PLUS;
    } else if (holdingButtonTick(buttonsDown & ClockButton::MINUS, &minusHoldtime)) {
        buttonsHeld |= ClockButton::MINUS;
    }
    return buttonsHeld;
}

bool holdingButtonTick(bool buttonDown, unsigned long * downTime) {
    if (buttonDown) {
        if (*downTime == 0) {
            *downTime = millis();
        } else if (millis() - *downTime > BUTTON_HOLD_TIMEOUT) {
            return true;
        }
    } else {
        *downTime = 0;
    }
    return false;
}

uint8_t queryButton(uint8_t pin, ClockButton button) {
    return (digitalRead(pin) == HIGH) ? (uint8_t)button : 0;
}

void triggerButtonsDown(uint8_t buttons) {
    if (buttons & ClockButton::TEMP) {
        if (state == HIDDEN_TIME || state == SHOW_TIME) {
            state = SHOW_TEMP;
        }
    } else if (buttons & ClockButton::ALARM1) {
        if (state == SHOW_TIME) {
            state = SHOW_ALARM1;
        }
    } else if (buttons & ClockButton::ALARM2) {
        if (state == SHOW_TIME) {
            state = SHOW_ALARM2;
        }
    }
    if (state == HIDDEN_TIME) {
        state = SHOW_TIME;
    }
}

void triggerButtonsPressed(uint8_t buttons) {
    switch (state) {
        case SHOW_TEMP:
            if (buttons & ClockButton::TEMP) {
                state = SHOW_TIME;
            }
            break;
        case SHOW_TIME:
            if (buttons & ClockButton::PLUS) {
                disp.brighten();
            }
            if (buttons & ClockButton::MINUS) {
                disp.dim();
            }
            if (buttons & ClockButton::ALARM1) {
                // TODO
                // enable alarm1
            }
            if (buttons & ClockButton::ALARM2) {
                // TODO
                // enable alarm2
            }
            break;
        case HIDDEN_TIME: // should't happen, but will recover if it does.
            state = SHOW_TIME;
            break;
        case SET_TIME:
            if (buttons & ClockButton::SET) {
                state = SET_HOUR;
            }
            break;
        case SET_HOUR:
            if (buttons & ClockButton::SET) {
                state = SET_MINUTE;
                break;
            }
            if (buttons & ClockButton::PLUS) {
                incrementSetHour();
            }
            if (buttons & ClockButton::MINUS) {
                decrementSetHour();
            }
            break;
        case SET_MINUTE:
            if (buttons & ClockButton::SET) {
                state = SHOW_TIME;
                saveSetTime();
                break;
            }
            if (buttons & ClockButton::PLUS) {
                incrementSettingMinute();
            }
            if (buttons & ClockButton::MINUS) {
                decrementSettingMinute();
            }
            break;
        case SET_ALARM1:
            if (buttons & ClockButton::SET) {
                state = SET_ALARM1_HOUR;
            }
            break;
        case SET_ALARM1_HOUR:
            if (buttons & ClockButton::SET) {
                state = SET_ALARM1_MINUTE;
                break;
            }
            if (buttons & ClockButton::PLUS) {
                incrementSetHour();
            }
            if (buttons & ClockButton::MINUS) {
                decrementSetHour();
            }
            break;
        case SET_ALARM1_MINUTE:
            if (buttons & ClockButton::SET) {
                state = SHOW_TIME;
                saveAlarm1();
                break;
            }
            if (buttons & ClockButton::PLUS) {
                incrementSettingMinute();
            }
            if (buttons & ClockButton::MINUS) {
                decrementSettingMinute();
            }
            break;
        case SET_ALARM2:
            if (buttons & ClockButton::SET) {
                state = SET_ALARM2_HOUR;
            }
            break;
        case SET_ALARM2_HOUR:
            if (buttons & ClockButton::SET) {
                state = SET_ALARM2_MINUTE;
                break;
            }
            if (buttons & ClockButton::PLUS) {
                incrementSetHour();
            }
            if (buttons & ClockButton::MINUS) {
                decrementSetHour();
            }
            break;
        case SET_ALARM2_MINUTE:
            if (buttons & ClockButton::SET) {
                state = SHOW_TIME;
                saveAlarm2();
                break;
            }
            if (buttons & ClockButton::PLUS) {
                incrementSettingMinute();
            }
            if (buttons & ClockButton::MINUS) {
                decrementSettingMinute();
            }
            break;
        case SHOW_ALARM1:
            if (buttons & ClockButton::ALARM1) {
                state = SHOW_TIME;
            }
            break;
        case SHOW_ALARM2:
            if (buttons & ClockButton::ALARM2) {
                state = SHOW_TIME;
            }
            break;
    }
}

void incrementSetHour() {
    settingHour++;
    if (settingHour > 23) {
        settingHour = 0;
    }
}

void decrementSetHour() {
    settingHour--;
    if (settingHour < 0) {
        settingHour = 23;
    }
}

void incrementSettingMinute() {
    settingMinute++;
    if (settingMinute > 59) {
        settingMinute = 0;
    }
}

void decrementSettingMinute() {
    settingMinute--;
    if (settingMinute < 0) {
        settingMinute = 59;
    }
}

bool blinkShouldShow() {
    static bool shouldShow = true;
    static unsigned long lastBlink = millis();
    if (millis() - lastBlink > BLINK_DELAY) {
        lastBlink = millis();
        shouldShow = !shouldShow;
    }
    return shouldShow;
}

void saveSetTime() {
    const RtcDateTime now = rtc.GetDateTime();
    const RtcDateTime set = RtcDateTime(now.Year(), now.Month(), now.Day(), settingHour, settingMinute, 0);
    rtc.SetDateTime(set);
}

void saveAlarm1() {
    // TODO
}

void saveAlarm2() {
    // TODO
}

void updateDisplay() {
    switch (state) {
        case SHOW_TIME:
            showTime();
            break;
        case INVALID_TIME:
            if (blinkShouldShow()) {
                disp.clear(CS_HOUR);
                disp.clear(CS_MINUTE15);
                disp.clear(CS_MINUTE1);
            } else {
                showTime();
            }
            break;
        case SHOW_TEMP:
            showTemp();
            break;
        case SET_TIME:
        case SET_ALARM1:
        case SET_ALARM2:
        case SET_HOUR:
        case SET_ALARM1_HOUR:
        case SET_ALARM2_HOUR:
            disp.showClockDigit(CS_MINUTE15, settingMinute / 15);
            disp.showClockDigit(CS_MINUTE1, settingMinute % 15);
            if (blinkShouldShow()) {
                disp.showClockDigit(CS_HOUR, settingHour);
            } else {
                disp.clear(CS_HOUR);
            }
            break;
        case SET_MINUTE:
        case SET_ALARM1_MINUTE:
        case SET_ALARM2_MINUTE:
            disp.showClockDigit(CS_HOUR, settingHour);
            if (blinkShouldShow()) {
                disp.showClockDigit(CS_MINUTE15, settingMinute / 15);
                disp.showClockDigit(CS_MINUTE1, settingMinute % 15);
            } else {
                disp.clear(CS_MINUTE15);
                disp.clear(CS_MINUTE1);
            }
            break;
    }
}

void triggerButtonsHeld(uint8_t buttons) {
    switch (state) {
        case SHOW_TIME:
            if (buttons & ClockButton::SET) {
                settingHour = rtc.GetDateTime().Hour();
                settingMinute = rtc.GetDateTime().Minute();
                state = SET_TIME;
            } else if (buttons & ClockButton::ALARM1) {
                settingHour = rtc.GetAlarmOne().Hour();
                settingMinute = rtc.GetAlarmOne().Minute();
                state = SET_ALARM1;
            } else if (buttons & ClockButton::ALARM2) {
                settingHour = rtc.GetAlarmTwo().Hour();
                settingMinute = rtc.GetAlarmTwo().Minute();
                state = SET_ALARM2;
            }
        case SET_HOUR:
        case SET_ALARM1_HOUR:
        case SET_ALARM2_HOUR:
            if (buttons & ClockButton::PLUS) {
                incrementSetHour();
                delay(200);
            } else if (buttons & ClockButton::MINUS) {
                decrementSetHour();
                delay(200);
            }
            break;
        case SET_MINUTE:
        case SET_ALARM1_MINUTE:
        case SET_ALARM2_MINUTE:
            if (buttons & ClockButton::PLUS) {
                incrementSettingMinute();
                delay(200);
            } else if (buttons & ClockButton::MINUS) {
                decrementSettingMinute();
                delay(200);
            }
            break;
    }
}

void showTemp() {
    RtcTemperature temp = rtc.GetTemperature();
    int tinf = (int)temp.AsFloatDegF();

    disp.showCharacter(CS_HOUR, 'T');
    
    // in base 10
    if (tinf < 0 ) {
        disp.showCharacter(CS_MINUTE15, '-');
    } else if (tinf > 100) {
        disp.showCharacter(CS_MINUTE15, '+');
    } else {
        disp.showCharacter(CS_MINUTE15, '0' + (tinf / 10));
    }
    
    if (tinf <= -10) {
        disp.showCharacter(CS_MINUTE1, 'L');
    } else if (tinf >= 100) {
        disp.showCharacter(CS_MINUTE1, 'H');
    } else {
        disp.showCharacter(CS_MINUTE1, '0' + (tinf % 10));
    }
}

void showTime() {
    static unsigned long lastTimeUpdate = 0;
    static bool hourTrans = false;
    static bool min16Trans = false;
    static bool min1Trans = false;
    static uint16_t transIndex = 8;
    static uint8_t lastHour = rtc.GetDateTime().Hour();
    static uint8_t lastMinute = rtc.GetDateTime().Minute();


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
        disp.showClockDigit(CS_MINUTE1, min1);
    }

    if (min16Trans) {
        disp.showTransition(CS_MINUTE15, transIndex, min15);
    } else {
        disp.showClockDigit(CS_MINUTE15, min15);
    }
    
    if (hourTrans) {
        disp.showTransition(CS_HOUR, transIndex, hour);
    } else {
        disp.showClockDigit(CS_HOUR, hour);
    }
    transIndex++;
    lastMinute = minute;
    lastHour = hour;
}
