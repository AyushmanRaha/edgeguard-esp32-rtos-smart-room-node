# Development

## Arduino IDE
Open `firmware/EdgeGuard_ESP32/EdgeGuard_ESP32.ino`. Keep all sibling `.h` and `.cpp` files in the same sketch directory so the Arduino IDE can compile the modular firmware.

## PlatformIO
From the repository root:

```bash
python -m pip install -r requirements.txt
pio run
```

## Module layout
Use `config.h` for constants, `types.h` for shared types, `app_state.*` for mutex-protected state, `sensors.*` for hardware reads, `control.*` for relay/state-machine logic, `wifi_manager.*` for Wi-Fi, `web_routes.*` for HTTP behavior, and `tasks.*` for FreeRTOS loops.

## Coding guidelines
- Preserve pins, relay polarity, LDR polarity, routes, and JSON field names unless docs and hardware are intentionally changed.
- Avoid holding the mutex during serial output, sensor reads, relay writes, web sends, or long string building.
- Keep sensor reads bounded, especially HC-SR04 echo timing.
- Keep `secrets.h` local and untracked.
- Keep dashboard changes minimal and local-only.
