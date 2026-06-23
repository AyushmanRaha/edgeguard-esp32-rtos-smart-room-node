# State machine

```text
BOOT -> CALIBRATING -> AUTO_MONITORING
                         | temp high
                         v
                       ALERT

Any mode + repeated sensor failures -> FAULT
MANUAL mode -> MANUAL_OVERRIDE
AWAY + nearby occupancy -> ALERT
```

## Priority order
1. FAULT: repeated DHT11 or HC-SR04 failures force both relays off.
2. MANUAL: dashboard relay buttons preserve selected relay states.
3. AWAY: nearby occupancy triggers ALERT and Relay 2; otherwise Relay 2 is off.
4. AUTO: dark plus occupied turns Relay 1 on; temperature alert turns Relay 2 on.

## Transition rules
- Five consecutive DHT11 failures set FAULT.
- Five consecutive HC-SR04 timeouts set FAULT.
- Temperature alert latches on at `TEMP_ALERT_ON_C` and clears at `TEMP_ALERT_OFF_C`.
- Occupancy is held until `UNOCCUPIED_TIMEOUT_MS` after the last nearby reading.
