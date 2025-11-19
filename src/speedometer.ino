#include <SPI.h>
#include <TFT_eSPI.h>
#include <gauge.h>

const int hallSensorPin = 4;

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
  
  Serial.print("Hall effect sensor reading: ");
  Serial.println(sensorValue);
  
  drawSpeedText(sensorValue); 

  delay(1000); // Pause at max speed
}