// TriSense Water Analysis - Arduino Code
// Description: Measures pH, Turbidity, and Water Level in real-time

// Pin Configurations
const int pH_pin = A0;
const int turbidity_pin = A1;
const int water_level_pin = A2;

// Calibration Offsets
float pH_offset = 0.0;
float turbidity_offset = 0.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Calibration...");

  long pH_sum = 0;
  long turbidity_sum = 0;

  // Take 100 readings for initial calibration
  for (int i = 0; i < 100; i++) {
    pH_sum += analogRead(pH_pin);
    turbidity_sum += analogRead(turbidity_pin);
    delay(10); // Stability delay
  }

  // Convert average analog readings to actual sensor values
  float avg_pH_value = pH_sum / 100.0;
  float avg_pH_voltage = avg_pH_value * (5.0 / 1023.0);
  float avg_pH = (avg_pH_voltage * 14.0) / 5.0; // Map 0–5V to pH 0–14

  float avg_turbidity_value = turbidity_sum / 100.0;
  float avg_turbidity = (avg_turbidity_value * 100.0) / 1023.0;

  // Assume current environment has pH 5.0 and turbidity 35% for offset calibration
  pH_offset = 5.0 - avg_pH;
  turbidity_offset = 35.0 - avg_turbidity;

  Serial.println("Calibration complete.");
}

void loop() {
  // --------- pH Sensor ---------
  int pH_value = analogRead(pH_pin);
  float pH_voltage = pH_value * (5.0 / 1023.0);
  float pH = (pH_voltage * 14.0) / 5.0 + pH_offset;

  // --------- Turbidity Sensor ---------
  int turbidity_value = analogRead(turbidity_pin);
  float turbidity = (turbidity_value * 100.0) / 1023.0 + turbidity_offset;

  // --------- Water Level Sensor ---------
  int water_level_value = analogRead(water_level_pin);
  float water_level_percent = (water_level_value * 100.0) / 1023.0;

  // --------- Serial Output ---------
  Serial.print("pH Value: ");
  Serial.print(pH, 2);
  Serial.print(" | Turbidity Level: ");
  Serial.print(turbidity, 2);
  Serial.print(" %");
  Serial.print(" | Water Level: ");
  Serial.print(water_level_percent, 2);
  Serial.println(" %");

  delay(1000); // Wait 1 second before next reading
}
