# Testing plan

## Host unit tests
Run `bash scripts/run_host_tests.sh`. Tests cover AUTO lighting, occupancy timeout/hold, temperature hysteresis, DHT and ultrasonic faults, MANUAL preservation, AWAY alert behavior, FAULT priority, and event-log ordering.

## Repository checks
Run `python3 scripts/validate_repo.py` and `python3 scripts/check_firmware_structure.py` to verify secrets handling, required files, frozen pin mappings, and forbidden new hardware/service requirements.

## Arduino compile check
CI uses Arduino CLI to install ESP32 board support and required libraries, creates dummy `secrets.h`, and compiles `firmware/EdgeGuard_ESP32` for `esp32:esp32:esp32`.

## Manual hardware tests
- Confirm dashboard opens over Wi-Fi or fallback AP.
- Cover/uncover LDR and move near HC-SR04 in AUTO.
- Test MANUAL relay buttons.
- Warm DHT11 enough to cross alert threshold.
- Disconnect DHT11 or block HC-SR04 echo to observe FAULT after repeated failures.
