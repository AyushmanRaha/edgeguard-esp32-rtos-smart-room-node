# Hardware

## Pin map
| Function | ESP32 GPIO | Notes |
| --- | ---: | --- |
| DHT11 DATA | 4 | Temperature/humidity data |
| HC-SR04 TRIG | 5 | Trigger output |
| HC-SR04 ECHO | 18 | Use a voltage divider to 3.3 V |
| LDR DO | 34 | Digital input only |
| Relay 1 | 26 | Active-low by default |
| Relay 2 | 27 | Active-low by default |
| Green LED | 23 | Heartbeat/status |
| Red LED | 22 | Alert/fault indication |

## Safety
Use low-voltage DC loads for prototyping. Do not place mains AC on a breadboard or exposed relay module. Keep sensor grounds common with the ESP32 ground, and level shift the HC-SR04 ECHO signal before GPIO 18.
