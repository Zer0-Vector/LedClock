# LedClock

A fairly simple implementation of a digital clock using the Arduino Nano. There are a few unique elements described in the next sections.

## Key Components
* HW-O84 Real-time clock module (DS3231)
* Three 8x8 LED matrix displays with MAX7219 drivers

## Non-standard digit base
I was constrained to using three 8x8 LED matrixes, so I altered the base for the hour and minutes:
* Hour is one digit in base 24 (0 - N).
* Minute is two "digits" in base 15 (0 - E).
    * The 15s digit is represented by a circle with the current quarter hour filled in, as if it was a mechanical clock face.

### Why base 15?
Originally, this was a hexadecimal clock. After some thought, I wanted to try base 15 since the 15s digit would represent the current quarter hour or quadrant of an analog clock. This seemed more logical given how we divide up the hour naturally.

I opted for a pictoral representation of the 15s digit (quarter hour) because it was too easy to glance at the clock and it register as a normal, base 10 clock. This way, it's clear that the representation is different and should be read differently.

## Temperature button
The real-time clock chip has a temperature sensor on it (for some reason). I thought it would be a shame to waste. Hold down the "Temp" button to display the temperature. The hour digit displays `T` when active.

## Off when idle switch
Called "always on" in the code, a switch is available which activates a five second timeout when showing the time. After time runs out, it shutsdown the MAX7219 chips to save power. See the MAX7219 datasheet for more information on its shutdown mode.

## Digit Transitions
When the time changes, the digits change with a "push down" transition. The next digit pushes the current digit down from the top, out the bottom.

## Character pixel arrays stored in program memory (`PROGMEM`)
I took advantage of the Arduino's program memory to store the static character pixel arrays. I was glad to find it still worked on class members since it was not mentioned in the [documentation](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/).
