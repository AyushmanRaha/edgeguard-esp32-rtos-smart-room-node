# Wiring Table

## ESP32 Pin Map

| ESP32 Pin | Component | Purpose |
|---|---|---|
| GPIO 4 | DHT11 DATA | Temperature/humidity input |
| GPIO 5 | HC-SR04 TRIG | Ultrasonic trigger |
| GPIO 18 | HC-SR04 ECHO through divider | Ultrasonic echo input |
| GPIO 34 | LDR DO | Digital light/dark input |
| GPIO 26 | Relay IN1 | Room light LED load |
| GPIO 27 | Relay IN2 | Alert LED load |
| GPIO 23 | Green LED | Heartbeat |
| GPIO 22 | Red LED | Alert/fault indication |
| 3V3 | DHT11, LDR | 3.3V sensor power |
| VIN/5V | HC-SR04, Relay module | 5V module power |
| GND | All modules | Common ground |

## HC-SR04 Echo Divider

HC-SR04 Echo is not connected directly to ESP32.

Wiring:

```text
Echo ---- 2.2kΩ ---- GPIO18 ---- 2.2kΩ ---- GND