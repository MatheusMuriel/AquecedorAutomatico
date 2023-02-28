#include <OneWire.h>

#define ONE_WIRE_BUS 0
OneWire TemperatureSensor(ONE_WIRE_BUS);

void setup(void) {
  //SerialUSB.begin();
  Serial.begin(9600);
}

void loop(void) {
  Serial.println(F("Teste"));
  byte i;
  byte data[12];
  int16_t raw;
  float t;
  TemperatureSensor.reset(); // reset one wire buss
  TemperatureSensor.skip(); // select only device
  TemperatureSensor.write(0x44); // start conversion
  delay(1000); // wait for the conversion
  TemperatureSensor.reset();
  TemperatureSensor.skip();
  TemperatureSensor.write(0xBE); // Read Scratchpad
  
  for (i = 0; i < 9; i++) { // 9 bytes
    data[i] = TemperatureSensor.read();
  }
  raw = (data[1] << 8) | data[0];
  t = (float)raw / 16.0;

  //SerialUSB.print(t);
  Serial.println(t);
}

