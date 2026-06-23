# Interview notes

## Recruiter explanation
EdgeGuard is a practical ESP32 embedded project that shows hardware integration, FreeRTOS-style task decomposition, a local web dashboard, safety-aware relay usage, and professional software practices such as unit tests and CI.

## Resume bullet variations
- Built an ESP32 smart-room node with DHT11, HC-SR04, LDR, relays, LEDs, and a local web dashboard.
- Refactored Arduino firmware into hardware IO and pure C++ control logic for host-side unit testing.
- Implemented AUTO, MANUAL, AWAY, ALERT, and FAULT modes with deterministic relay safety behavior.
- Added GitHub Actions CI to run host tests, validation scripts, and Arduino CLI compile checks.
- Designed fault handling for repeated DHT11 and HC-SR04 failures with relays forced off.
- Documented safe low-voltage relay wiring and HC-SR04 Echo level shifting for ESP32 GPIO.
- Used FreeRTOS-style tasks to separate sensing, control, web serving, and heartbeat indicators.
- Created an interview-ready embedded portfolio project without cloud services or paid dependencies.

## Common questions
**Why ESP32?** It has Wi-Fi, enough GPIO, Arduino IDE support, and FreeRTOS under the Arduino core.

**Why FreeRTOS-style tasks?** Tasks keep sensing, control, web serving, and LED heartbeat responsive without a single blocking loop.

**Why split pure logic from hardware IO?** It lets the same state-machine decisions compile and run on a laptop, so behavior can be tested without sensors attached.

**How did you protect ESP32 from HC-SR04 Echo?** Echo is divided down with resistors before GPIO18 so the ESP32 never receives a 5 V signal.

**What does CI verify without hardware?** It runs C++ host tests, checks frozen pins and required files, and compiles the Arduino sketch with dummy credentials.

**What would you improve next?** Add more telemetry history, calibrate thresholds per room, and add optional nonvolatile settings while keeping the same hardware.
