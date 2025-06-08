# 💧 TriSense-Water-Analysis

A **Low-Cost Arduino-Based Water Quality Monitoring System** for real-time analysis of **pH**, **turbidity**, and **water level**. Built using Arduino Uno and basic analog sensors, this DIY project helps in environmental monitoring, education, and water safety assessment.

---

## 📌 Features

- Real-time measurement of:
  - 🧪 pH Level (0–14 scale)
  - 🌫 Turbidity (0–100%)
  - 🌊 Water Level (0–100%)
- Automatic sensor calibration on startup
- Serial output for live monitoring
- Easy to extend for IoT (Blynk/ThingSpeak) and LCD displays

---

## 🧰 Hardware Requirements

- Arduino Uno
- pH Sensor (e.g., PH-4502C)
- Turbidity Sensor (e.g., SEN0189)
- Water Level Sensor (Conductive or Analog)
- Jumper wires and Breadboard
- USB Cable or 9V Battery

---

## 🛠️ How to Use

1. **Connect Sensors**:
   - `pH sensor` to `A0`
   - `Turbidity sensor` to `A1`
   - `Water level sensor` to `A2`

2. **Upload Code** via Arduino IDE

3. **Open Serial Monitor** (9600 baud) to view data

4. Keep sensors in known clean water during power-up for proper calibration

---

## 💾 Source Code

```cpp
// TriSense Water Analysis - Arduino Code

const int pH_pin = A0;
const int turbidity_pin = A1;
const int water_level_pin = A2;

float pH_offset = 0.0;
float turbidity_offset = 0.0;

void setup() {
  Serial.begin(9600);
  long pH_sum = 0;
  long turbidity_sum = 0;

  for (int i = 0; i < 100; i++) {
    pH_sum += analogRead(pH_pin);
    turbidity_sum += analogRead(turbidity_pin);
    delay(10);
  }

  float avg_pH_value = pH_sum / 100.0;
  float avg_pH_voltage = avg_pH_value * (5.0 / 1023.0);
  float avg_pH = (avg_pH_voltage * 14.0) / 5.0;

  float avg_turbidity_value = turbidity_sum / 100.0;
  float avg_turbidity = (avg_turbidity_value * 100.0) / 1023.0;

  pH_offset = 5.0 - avg_pH;
  turbidity_offset = 35.0 - avg_turbidity;

  Serial.println("Calibration complete.");
}

void loop() {
  int pH_value = analogRead(pH_pin);
  float pH_voltage = pH_value * (5.0 / 1023.0);
  float pH = (pH_voltage * 14.0) / 5.0 + pH_offset;

  int turbidity_value = analogRead(turbidity_pin);
  float turbidity = (turbidity_value * 100.0) / 1023.0 + turbidity_offset;

  int water_level_value = analogRead(water_level_pin);
  float water_level_percent = (water_level_value * 100.0) / 1023.0;

  Serial.print("pH Value: ");
  Serial.print(pH, 2);
  Serial.print(" | Turbidity Level: ");
  Serial.print(turbidity, 2);
  Serial.print(" %");
  Serial.print(" | Water Level: ");
  Serial.print(water_level_percent, 2);
  Serial.println(" %");

  delay(1000);
}

```

## 📈 Example Output
```
Calibration complete.
pH Value: 6.85 | Turbidity Level: 34.75 % | Water Level: 88.23 %

```
--------
## 🚀 Future Enhancements
1. 📲 Add Wi-Fi module (ESP8266/NodeMCU) for Blynk or ThingSpeak integration

2. 💾 Add SD card support for local data logging

3. 🔋 Add solar + battery support for remote monitoring

4. 📱 Create a mobile app or dashboard for live data view

--------