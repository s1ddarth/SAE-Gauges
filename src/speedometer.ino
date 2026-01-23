#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL 48
#define NUM_PIXELS 1

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup(){
  Serial.begin(115200);
  delay(1000);
  
  pixels.begin();
  pixels.show();
  
  Serial.println("STARTING");
  Serial.println("LED initialized");
}

void loop() {
  // Red
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();
  Serial.println("LED: Red");
  delay(1000);
  
  // Green
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
  Serial.println("LED: Green");
  delay(1000);
  
  // Blue
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  Serial.println("LED: Blue");
  delay(1000);
  
  // Off
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  Serial.println("LED: Off");
  delay(1000);
}