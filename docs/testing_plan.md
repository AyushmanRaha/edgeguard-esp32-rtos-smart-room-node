# Testing Plan

## Test 1: ESP32 boot

Expected:
- Serial Monitor starts at 115200 baud.
- Boot logs appear.

## Test 2: DHT11

Expected:
- Temperature and humidity values appear.
- If disconnected, FAULT state appears after repeated failures.

## Test 3: HC-SR04

Expected:
- Distance value changes when object moves.
- Occupancy becomes YES when object is within threshold.

## Test 4: LDR

Expected:
- Covering sensor changes dashboard to DARK.
- Light exposure changes dashboard to BRIGHT.

## Test 5: Relay 1

Expected:
- AUTO mode: dark + occupied turns Relay 1 ON.
- Unoccupied timeout turns Relay 1 OFF.

## Test 6: Relay 2

Expected:
- AWAY mode + movement turns Relay 2 ON.
- Manual button can turn Relay 2 ON/OFF.

## Test 7: Web dashboard

Expected:
- `/` displays dashboard.
- `/api/status` returns JSON.
- `/api/logs` returns event log.