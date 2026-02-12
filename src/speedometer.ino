#include <Arduino.h>

#define ONBOARD_LED 38
// Onboard LED is GPIO 38

void setup(){
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("STARTING");
}

void loop() {
  int i = 1;
  Serial.println("Looping: " + i);
  delay(1000);
}