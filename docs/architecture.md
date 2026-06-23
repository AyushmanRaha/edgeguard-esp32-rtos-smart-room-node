# Architecture

EdgeGuard-ESP32 is a real-time smart room monitoring node built on ESP32.

## Main firmware blocks

1. SensorTask
   - Reads DHT11, HC-SR04, and LDR.
   - Updates the shared sensor snapshot.

2. ControlTask
   - Runs the state machine.
   - Handles occupancy detection.
   - Applies relay decisions.
   - Detects fault conditions.

3. WebTask
   - Serves a local dashboard.
   - Provides JSON endpoints.
   - Handles manual mode and relay controls.

4. HeartbeatTask
   - Blinks green LED during normal operation.
   - Blinks red LED during ALERT or FAULT.

## Data flow

```text
Sensors
  ↓
SensorTask
  ↓
Shared Sensor Snapshot
  ↓
ControlTask
  ↓
Relay Driver + Event Log + System Snapshot
  ↓
Web Dashboard