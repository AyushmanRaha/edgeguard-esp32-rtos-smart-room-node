# EdgeGuard Agent Notes

## Project summary
EdgeGuard is an Arduino IDE compatible ESP32 DevKit smart-room node using DHT11, HC-SR04, LDR digital module, two-channel relay module, green heartbeat LED, red alert/fault LED, and low-voltage LED relay loads.

## Hard rules
- Hardware freeze: do not change `firmware/EdgeGuard_ESP32/config.h` pin mappings or require new hardware.
- Safety: relays switch low-voltage LED loads only. Do not document or encourage AC mains wiring.
- Keep Arduino IDE compatibility. Main sketch stays `firmware/EdgeGuard_ESP32/EdgeGuard_ESP32.ino`.
- Keep Wi-Fi credentials in `firmware/EdgeGuard_ESP32/secrets.h` only; never commit real credentials. Keep `secrets.h` ignored.
- Do not add paid services, cloud dependencies, Firebase, Blynk, MQTT, ESP-IDF requirements, or PlatformIO requirements.
- Prefer small, reviewable changes over rewrites.

## Tests and CI
Run before handing off when practical:
- `bash scripts/run_host_tests.sh`
- `python3 scripts/validate_repo.py`
- `python3 scripts/check_firmware_structure.py`

CI should run host tests, repository validation, firmware structure checks, and an Arduino CLI compile for `esp32:esp32:esp32` without uploading hardware.

## Documentation expectations
Update README and relevant docs when changing behavior, architecture, setup, tests, wiring explanations, or dashboard/API details.
