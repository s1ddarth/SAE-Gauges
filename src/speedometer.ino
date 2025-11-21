#include <SPI.h>
#include <TFT_eSPI.h>
#include <gauge.h>

const int hallSensorPin = 4;

// Define the TFT display instance
TFT_eSPI tft = TFT_eSPI(); 

void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println("STARTING");
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  tft.init();
  Serial.println("TFT INITIALIZED");
  tft.fillScreen(TFT_WHITE);

}

void loop() {
  int sensorValue = analogRead(hallSensorPin);
  
  Serial.print("Hall effect sensor reading: ");
  Serial.println(sensorValue);

  delay(1000); // Pause at max speed
}