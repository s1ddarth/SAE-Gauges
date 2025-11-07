/*
 * ESP32 Speedometer for 240x240 Round GC9A01 Display
 *
 * This code demonstrates how to draw a speedometer gauge and animate a needle.
 *
 * v2: Fixed graphics bug causing "sunburst" effect by adjusting gauge
 * geometry so the needle and static arc do not overlap.
 *
 * HARDWARE SETUP (based on user photos/description):
 * Display -> ESP32
 * VCC     -> 3.3V
 * GND     -> GND
 * SCL     -> GPIO 18 (D18)
 * SDA     -> GPIO 23 (D23)
 * DC      -> GPIO 2 (D2)
 * CS      -> GPIO 4 (D4)
 * RST     -> GPIO 5 (D5)
 * BLK     -> (Not connected, seems to be on by default)
 *
 * LIBRARY SETUP:
 * This code REQUIRES the 'TFT_eSPI' library by Bodmer.
 * You MUST configure this library for your specific setup.
 * Please see the 'README_Library_Setup.md' file for instructions.
 */

#include <SPI.h>
#include <TFT_eSPI.h>
#include <gauge.h>

const int hallSensorPin = 34; 

// Define the TFT display instance
TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  Serial.begin(115200);
  Serial.println("GC9A01 Speedometer Test v2");

  // Initialize the TFT display
  tft.init();
  tft.setRotation(0); 
  
  // Set text datum to Middle Center for easy centering
  tft.setTextDatum(MC_DATUM); 

  tft.fillScreen(GAUGE_BG_COLOR);
  pinMode(hallSensorPin, INPUT);

  // Draw the static parts of the gauge
  drawGauge();
}

void loop() {

  int sensorValue = analogRead(hallSensorPin);
  drawSpeedText(sensorValue); 

  delay(100); // Pause at max speed
}