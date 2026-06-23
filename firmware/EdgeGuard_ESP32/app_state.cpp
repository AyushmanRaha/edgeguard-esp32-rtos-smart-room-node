#include "app_state.h"

namespace {
SemaphoreHandle_t gMutex = nullptr;
SensorSnapshot gSensor;
SystemSnapshot gSystem;
String gEvents[EVENT_LOG_SIZE];
uint8_t gEventHead = 0;
uint8_t gEventCount = 0;

bool takeMutex(TickType_t timeout = pdMS_TO_TICKS(50)) {
  return gMutex != nullptr && xSemaphoreTake(gMutex, timeout) == pdTRUE;
}
}

const char* modeName(Mode mode) {
  switch (mode) {
    case Mode::AUTO: return "AUTO";
    case Mode::MANUAL: return "MANUAL";
    case Mode::AWAY: return "AWAY";
    default: return "UNKNOWN";
  }
}

const char* stateName(State state) {
  switch (state) {
    case State::BOOT: return "BOOT";
    case State::CALIBRATING: return "CALIBRATING";
    case State::AUTO_MONITORING: return "AUTO_MONITORING";
    case State::MANUAL_OVERRIDE: return "MANUAL_OVERRIDE";
    case State::ALERT: return "ALERT";
    case State::FAULT: return "FAULT";
    default: return "UNKNOWN";
  }
}

bool initAppState() {
  gMutex = xSemaphoreCreateMutex();
  if (gMutex == nullptr) return false;
  return markCriticalFault("") || true;
}

bool markCriticalFault(const String& reason) {
  if (!takeMutex()) return false;
  gSystem.state = reason.length() ? State::FAULT : State::CALIBRATING;
  gSystem.mode = Mode::AUTO;
  gSystem.relay1On = false;
  gSystem.relay2On = false;
  gSystem.faultReason = reason;
  gSystem.timestampMs = millis();
  xSemaphoreGive(gMutex);
  return true;
}

bool updateSensorSnapshot(const SensorSnapshot& snapshot) {
  if (!takeMutex()) return false;
  gSensor = snapshot;
  xSemaphoreGive(gMutex);
  return true;
}

bool updateSystemSnapshot(const SystemSnapshot& snapshot) {
  if (!takeMutex()) return false;
  gSystem = snapshot;
  xSemaphoreGive(gMutex);
  return true;
}

bool copySensorSnapshot(SensorSnapshot& out) {
  if (!takeMutex()) return false;
  out = gSensor;
  xSemaphoreGive(gMutex);
  return true;
}

bool copySystemSnapshot(SystemSnapshot& out) {
  if (!takeMutex()) return false;
  out = gSystem;
  xSemaphoreGive(gMutex);
  return true;
}

uint8_t copyEventLog(String (&out)[EVENT_LOG_SIZE]) {
  if (!takeMutex()) return 0;
  const uint8_t count = gEventCount;
  const uint8_t start = (gEventHead + EVENT_LOG_SIZE - gEventCount) % EVENT_LOG_SIZE;
  for (uint8_t i = 0; i < count; i++) out[i] = gEvents[(start + i) % EVENT_LOG_SIZE];
  xSemaphoreGive(gMutex);
  return count;
}

String jsonEscape(String value) {
  value.replace("\\", "\\\\");
  value.replace("\"", "\\\"");
  value.replace("\n", "\\n");
  return value;
}

void logEvent(const String& message) {
  char prefix[18];
  snprintf(prefix, sizeof(prefix), "[%lus] ", static_cast<unsigned long>(millis() / 1000));
  String line = String(prefix) + message;
  if (takeMutex()) {
    gEvents[gEventHead] = line;
    gEventHead = (gEventHead + 1) % EVENT_LOG_SIZE;
    if (gEventCount < EVENT_LOG_SIZE) gEventCount++;
    xSemaphoreGive(gMutex);
  }
  Serial.println(line);
}
