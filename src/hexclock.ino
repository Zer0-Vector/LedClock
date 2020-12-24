#include <LedControl.h>

LedControl lc = LedControl(12,11,10,3);

void setup() {
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
}


// delay time between faces
unsigned long delaytime=1000;

byte zero[8] = {
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

byte one[8] = {
    B00011000,
    B00111000,
    B01011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110
};

byte two[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111110
};

byte three[8] = {
    B00111100,
    B01000010,
    B00000010,
    B00011100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

byte four[8] = {
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111110,
    B00000100,
    B00000100,
    B00000100
};

byte five[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B00000010,
    B00000010,
    B01000010,
    B00111100
};

byte six[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

byte seven[8] = {
    B01111110,
    B01000010,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B01000000
};

byte eight[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B01000010,
    B01000010,
    B01000010,
    B00111100
};

byte nine[8] = {
    B00111100,
    B01000010,
    B01000010,
    B00111100,
    B00000100,
    B00001000,
    B00010000,
    B00100000
};

byte ten[8] = {
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010
};

byte eleven[8] = {
    B01111100,
    B01000010,
    B01000010,
    B01111100,
    B01000010,
    B01000010,
    B01000010,
    B01111100
};

byte twelve[8] = {
    B00111100,
    B01000010,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000010,
    B00111100
};

byte thirteen[8] = {
    B01111000,
    B01000100,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000100,
    B01111000
};

byte fourteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01111110
};

byte fifteen[8] = {
    B01111110,
    B01000000,
    B01000000,
    B01111100,
    B01000000,
    B01000000,
    B01000000,
    B01000000
};

void draw(int addr, byte pixels[8]) {
    lc.setRow(addr,0,pixels[0]);
    lc.setRow(addr,1,pixels[1]);
    lc.setRow(addr,2,pixels[2]);
    lc.setRow(addr,3,pixels[3]);
    lc.setRow(addr,4,pixels[4]);
    lc.setRow(addr,5,pixels[5]);
    lc.setRow(addr,6,pixels[6]);
    lc.setRow(addr,7,pixels[7]);
}

#define DELAY 250

unsigned long m = millis();

bool transitioning = false;
uint8_t transIndex = 0;

// byte currentHour = 0;
// byte currentMin16 = 0;
// byte currentMin = 0;

// byte prevHour = 0;
// byte prevMin16 = 0;
// byte prevMin = 0;

void loop() {
    // if (transitioning) {
    //     tickTransition();
    // }
    if (millis() - m >= DELAY) {
        tick();
        m = millis();
    }
}

// void tickTransition() {
//     byte t[8];
//     uint8_t ti = 0;
//     for (int i = 0; i < 8 - (transIndex + 1); i++) {
//         t[ti++] = getDigit();
//     }
// }

void tick() {
    static byte hour = 12;
    static byte minute = 0;
    setHour(hour);
    setMinute(minute);
    minute = (minute + 1) % 60;
    if (minute == 0) {
        hour = (hour + 1) % 12;
        if (hour == 0) {
            hour = 12;
        }
    }
    transitioning = true;
}

void setHour(byte hour) {
    draw(2, getDigit(hour));
}

void setMinute(byte minute) {
    draw(1, getDigit((minute & 0xF0) >> 4));
    draw(0, getDigit(minute & 0x0F));
}

byte* getDigit(byte digit) {
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
