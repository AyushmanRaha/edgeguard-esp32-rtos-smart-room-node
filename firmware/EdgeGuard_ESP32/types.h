#pragma once

#include <Arduino.h>

// -------------------- ENUMS --------------------
enum class Mode : uint8_t {
  AUTO,
  MANUAL,
  AWAY
};

enum class State : uint8_t {
  BOOT,
  CALIBRATING,
  AUTO_MONITORING,
  MANUAL_OVERRIDE,
  ALERT,
  FAULT
};

struct SensorSnapshot {
  float temperatureC = NAN;
  float humidity = NAN;
  bool dhtOk = false;
  uint16_t distanceCm = 0;
  bool distanceOk = false;
  bool ldrRawHigh = false;
  bool lightIsDark = false;
  uint32_t timestampMs = 0;
};

struct SystemSnapshot {
  Mode mode = Mode::AUTO;
  State state = State::BOOT;
  bool occupied = false;
  bool relay1On = false;
  bool relay2On = false;
  bool temperatureAlert = false;
  String faultReason = "";
  uint32_t timestampMs = 0;
};

const char* modeName(Mode mode);
const char* stateName(State state);
