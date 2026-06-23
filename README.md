# EdgeGuard-ESP32: RTOS-Style Smart Room Monitoring and Control Node

EdgeGuard-ESP32 is an embedded firmware project built on ESP32. It monitors room conditions using DHT11, HC-SR04, and LDR sensors, then controls low-voltage relay-driven LED loads through an RTOS-style task architecture and a local web dashboard.

## Features

- Temperature and humidity monitoring using DHT11
- Distance-based occupancy detection using HC-SR04
- Light/dark detection using LDR module
- Relay-based low-voltage LED load control
- AUTO, MANUAL, and AWAY modes
- ALERT and FAULT states
- Local Wi-Fi dashboard
- REST-style JSON status endpoint
- Event ring buffer
- FreeRTOS-style task separation

## Hardware Used

- ESP32 DevKit
- DHT11 module
- HC-SR04 ultrasonic sensor
- LDR digital sensor module
- 2-channel relay module
- LEDs
- 330Ω resistors
- 2.2kΩ resistors
- Breadboard
- Jumper wires

## Safety Note

This project does not use 230V AC mains. The relay module switches only low-voltage LEDs for demonstration.

## Firmware Architecture

```text
SensorTask
  ↓
Shared Sensor Snapshot
  ↓
ControlTask
  ↓
Relay Driver + State Machine + Event Log
  ↓
WebTask Dashboard