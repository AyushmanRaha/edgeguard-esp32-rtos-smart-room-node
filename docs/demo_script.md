# Demo script

## 2-minute demo
1. Show the hardware and state that no AC mains are used.
2. Open the dashboard and point out mode, state, sensors, relays, and logs.
3. In AUTO, cover the LDR and move near HC-SR04 to turn Relay 1 on.
4. Use MANUAL buttons to show direct relay control.
5. Explain that CI and host tests verify logic without hardware.

## 5-minute technical demo
1. Explain task split: SensorTask, ControlTask, WebTask, HeartbeatTask.
2. Show `edgeguard_control.cpp` and explain pure logic with injected time.
3. Run `bash scripts/run_host_tests.sh` locally.
4. Show the wiring table and Echo voltage divider.
5. Demonstrate AUTO, MANUAL, and AWAY behavior on the dashboard.
6. Explain FAULT priority and relay-off safety behavior.
