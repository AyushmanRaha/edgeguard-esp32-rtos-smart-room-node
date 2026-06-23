# Interview Notes

## Project summary

EdgeGuard-ESP32 is a real-time embedded smart room node using ESP32, DHT11, HC-SR04, LDR module, relay module, LEDs, and a local web dashboard.

## What I implemented

- Sensor acquisition using GPIO and timing logic.
- HC-SR04 echo protection using resistor voltage divider.
- Real-time task separation using FreeRTOS-style tasks.
- State machine for AUTO, MANUAL, AWAY, ALERT, and FAULT modes.
- Relay driver abstraction with active-low configuration.
- Event ring buffer for diagnostics.
- Local dashboard with REST-style endpoints.

## Important design choices

- I avoided 230V AC mains and used low-voltage LEDs as relay loads.
- I used a timeout for occupancy so the relay does not chatter.
- I added temperature hysteresis to avoid rapid ON/OFF switching.
- I added fault detection for repeated DHT11 or HC-SR04 failures.

## Possible future improvements

- Move from Arduino IDE to ESP-IDF.
- Add non-volatile settings storage using NVS.
- Add MQTT support.
- Add OTA firmware updates.
- Add unit tests for the state machine.
- Add power profiling.