#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000
int counter = 0;

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x02);
}

void loop() {
}
