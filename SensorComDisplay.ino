#include <TM1637TinyDisplay.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 0
#define CLK 4
#define DIO 3
#define TEMPERATURA_IDEAL 70

OneWire TemperatureSensor(ONE_WIRE_BUS);
TM1637TinyDisplay display(CLK, DIO);

void setup(void) {
  pinMode(1, OUTPUT); // Sinal para o Relé
  pinMode(3, OUTPUT); // Sinal para o Display
  digitalWrite(1, LOW);
  display.begin();
}

void loop(void) {
  TemperatureSensor.reset(); // reset one wire buss
  TemperatureSensor.skip(); // select only device
  TemperatureSensor.write(0x44); // start conversion
  delay(1000); // wait for the conversion
  TemperatureSensor.reset();
  TemperatureSensor.skip();
  TemperatureSensor.write(0xBE); // Read Scratchpad
  
  byte data[12];
  for (byte i = 0; i < 9; i++) { // 9 bytes
    data[i] = TemperatureSensor.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  int16_t temperatura = (int16_t)raw / 16.0;

  display.showNumber(temperatura);
  if (temperatura >= TEMPERATURA_IDEAL){
    digitalWrite(1, HIGH); // Desliga o relé
  } else if (temperatura < TEMPERATURA_IDEAL) {
    digitalWrite(1, LOW); // Deixa ligado o relé
  }
  
  delay(3000);
}