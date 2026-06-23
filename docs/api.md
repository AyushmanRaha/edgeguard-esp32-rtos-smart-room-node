# HTTP API

All routes are served by the ESP32 local web server. Normal command responses remain `{"ok":true}`. If a command cannot update shared state, the firmware returns HTTP `503` with `{"ok":false,"error":"state_unavailable"}`.

## Routes
| Method | Route | Response |
| --- | --- | --- |
| GET | `/` | HTML dashboard |
| GET | `/api/status` | Status JSON |
| GET | `/api/logs` | JSON array of event strings |
| POST | `/api/mode/auto` | `{"ok":true}` |
| POST | `/api/mode/manual` | `{"ok":true}` |
| POST | `/api/mode/away` | `{"ok":true}` |
| POST | `/api/relay1/on` | `{"ok":true}` |
| POST | `/api/relay1/off` | `{"ok":true}` |
| POST | `/api/relay2/on` | `{"ok":true}` |
| POST | `/api/relay2/off` | `{"ok":true}` |

## Status fields
- `temperature_c`: DHT11 temperature or `null`.
- `humidity`: DHT11 humidity or `null`.
- `dht_ok`: DHT11 read status.
- `distance_cm`: HC-SR04 distance or `null`.
- `distance_ok`: HC-SR04 echo status.
- `light_is_dark`: interpreted LDR darkness flag.
- `occupied`: occupancy after hold timeout logic.
- `mode`: `AUTO`, `MANUAL`, or `AWAY`.
- `state`: `BOOT`, `CALIBRATING`, `AUTO_MONITORING`, `MANUAL_OVERRIDE`, `ALERT`, or `FAULT`.
- `relay1`, `relay2`: commanded relay states.
- `temperature_alert`: temperature hysteresis latch.
- `fault_reason`: active fault text or empty string.
- `uptime_s`: uptime in seconds.
- `wifi_mode`: `STA` or `AP`.
- `ip`: current dashboard IP address.
- `heap_free`: free heap bytes.
- `rssi`: station RSSI when connected in station mode.
