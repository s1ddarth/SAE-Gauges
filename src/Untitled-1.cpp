// Define the GPIO pin connected to the 49E sensor's analog output
const int hallSensorPin = 34; // Example pin, adjust as needed (use an ADC pin)


void setup() {
  // Initialize serial communication to view sensor readings
  Serial.begin(115200);
 
  // Set the sensor pin as an input
  pinMode(hallSensorPin, INPUT);
 
  // Optional: Set ADC resolution for consistent reading (default is often 12-bit)
  // analogSetResolution(12); // 12-bit (0-4095)
}


void loop() {
  // Read the raw analog value (0-4095 for 12-bit)
 
  int sensorValue = analogRead(hallSensorPin);


  // Convert the raw reading to voltage (assuming 3.3V VCC)
  // float voltage = sensorValue * (3.3 / 4095.0);


  // Print the raw sensor value for feedback
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue % 2);
 
  // Optional: Print the converted voltage
  // Serial.print("Voltage (V): ");
  // Serial.println(voltage);
 
  delay(100); // Wait for half a second before the next reading
}