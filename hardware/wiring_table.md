# Wiring Table

| Device | Signal | ESP32 GPIO | Electrical note |
| --- | --- | ---: | --- |
| DHT11 | DATA | 4 | Use normal DHT11 module wiring |
| HC-SR04 | TRIG | 5 | ESP32 output |
| HC-SR04 | ECHO | 18 | Divide 5 V echo to 3.3 V |
| LDR module | DO | 34 | Digital input |
| Relay module | IN1 | 26 | `RELAY_ACTIVE_LOW = true` |
| Relay module | IN2 | 27 | `RELAY_ACTIVE_LOW = true` |
| Green LED | Anode/control | 23 | Use suitable resistor/module |
| Red LED | Anode/control | 22 | Use suitable resistor/module |

All examples assume low-voltage DC prototyping only.
