# Firmware architecture

EdgeGuard keeps Arduino IDE compatibility while separating testable decisions from hardware IO.

## Arduino integration layer
`firmware/EdgeGuard_ESP32/EdgeGuard_ESP32.ino` owns Arduino headers, Wi-Fi, WebServer, DHT library use, GPIO reads/writes, FreeRTOS tasks, and HTML/JSON endpoints.

## Pure control logic
`edgeguard_control.cpp` receives `SensorSnapshot`, previous `SystemSnapshot`, `ControlContext`, config, and time in milliseconds. It returns desired state and relay outputs without calling Arduino APIs. This makes FAULT, AUTO, AWAY, MANUAL, hysteresis, and occupancy timeout testable on a laptop.

## Event log
`edgeguard_event_log.cpp` is a fixed-size ring buffer. It avoids heap requirements and works in both host tests and Arduino builds.

## Why host tests are possible
The decision code depends only on plain C++ types and an injected timestamp. The host build compiles the same `.cpp` files with CMake and assert-based tests.
