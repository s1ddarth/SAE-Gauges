#include <Arduino.h>

const int hallPin = 2;
const int ledPin = 13;  // built-in

void setup() {
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int val = digitalRead(hallPin);
  digitalWrite(ledPin, val ? LOW : HIGH);
  delay(10);
}