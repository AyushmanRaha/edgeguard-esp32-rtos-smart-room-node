# AGENTS.md

## Project summary
EdgeGuard ESP32 is a low-voltage Arduino/FreeRTOS smart-room node for local sensing, relay control, and an onboard HTTP dashboard/API.

## Build and verification commands
- `pio run`
- `python tools/verify_repo.py`

## Hardware invariants
Preserve this pin map: DHT11 DATA GPIO 4, HC-SR04 TRIG GPIO 5, HC-SR04 ECHO GPIO 18 through a voltage divider, LDR DO GPIO 34, Relay 1 GPIO 26, Relay 2 GPIO 27, green LED GPIO 23, red LED GPIO 22. Keep `RELAY_ACTIVE_LOW = true` and `LDR_DARK_WHEN_HIGH = true` unless hardware documentation is deliberately changed.

## API invariants
Preserve the public routes documented in `docs/api.md`, including `/`, `/api/status`, `/api/logs`, mode POST routes, and relay POST routes. Keep normal command responses as `{"ok":true}` and keep status JSON field names stable.

## Safety rules
- Low-voltage DC prototyping only.
- Do not add mains AC wiring instructions beyond safety warnings.
- Never commit real Wi-Fi credentials, tokens, or secrets.

## Editing rules
- Use small, focused patches.
- Do not rewrite `dashboard.h` unless a behavior-preserving fix requires it.
- Preserve Arduino IDE compatibility: `firmware/EdgeGuard_ESP32/EdgeGuard_ESP32.ino` must open and build with the sibling modules.
- Preserve PlatformIO compatibility: `pio run` must work from the repository root.
- Keep repository text neutral and technical; do not add company or nontechnical positioning language.

## Documentation requirements
Update README and relevant docs when changing pins, routes, operating modes, build steps, or safety assumptions.
