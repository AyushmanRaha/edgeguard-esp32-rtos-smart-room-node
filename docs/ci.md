# CI

The workflow in `.github/workflows/ci.yml` runs on pull requests, pushes to `main`, and manual dispatch.

## host-tests job
Installs CMake/build tools, runs `scripts/run_host_tests.sh`, validates repo hygiene, and checks firmware structure.

## arduino-compile job
Installs Arduino CLI, ESP32 Arduino core, DHT sensor library, and Adafruit Unified Sensor. It writes dummy CI credentials and compiles the sketch for `esp32:esp32:esp32` without uploading.

## Why Arduino compile CI matters
It catches missing includes, syntax errors, library issues, and accidental Arduino IDE incompatibility before a student tries to upload.

## Why host tests matter
They verify state-machine behavior quickly on any development laptop, including an M1 MacBook, without needing the ESP32 connected.
