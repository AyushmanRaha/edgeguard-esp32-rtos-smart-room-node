#pragma once

#include <Arduino.h>
#include "config.h"
#include "types.h"

bool initAppState();
bool markCriticalFault(const String& reason);
bool updateSensorSnapshot(const SensorSnapshot& snapshot);
bool updateSystemSnapshot(const SystemSnapshot& snapshot);
bool copySensorSnapshot(SensorSnapshot& out);
bool copySystemSnapshot(SystemSnapshot& out);
uint8_t copyEventLog(String (&out)[EVENT_LOG_SIZE]);
void logEvent(const String& message);
String jsonEscape(String value);
