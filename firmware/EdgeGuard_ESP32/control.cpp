#include "control.h"
#include "app_state.h"
#include "config.h"

namespace {
uint8_t saturatingInc(uint8_t value) { return value < UINT8_MAX ? value + 1 : UINT8_MAX; }

void writeRelayPin(uint8_t pin, bool on) {
  digitalWrite(pin, RELAY_ACTIVE_LOW ? (on ? LOW : HIGH) : (on ? HIGH : LOW));
}
}

void applyRelays(bool relay1On, bool relay2On) {
  writeRelayPin(PIN_RELAY1, relay1On);
  writeRelayPin(PIN_RELAY2, relay2On);
}

void forceRelaysOff() { applyRelays(false, false); }

void setupPins() {
  pinMode(PIN_DHT, INPUT);
  pinMode(PIN_HCSR04_TRIG, OUTPUT);
  pinMode(PIN_HCSR04_ECHO, INPUT);
  pinMode(PIN_LDR_DO, INPUT);
  pinMode(PIN_RELAY1, OUTPUT);
  pinMode(PIN_RELAY2, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  forceRelaysOff();
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED, LOW);
}

void updateControl(const SensorSnapshot& sensor) {
  static uint8_t dhtFailCount = 0;
  static uint8_t ultrasonicFailCount = 0;
  static bool temperatureAlertLatched = false;
  static uint32_t lastOccupiedMs = 0;
  static bool hasEverSeenOccupancy = false;
  static State previousState = State::BOOT;
  static bool previousRelay1 = false;
  static bool previousRelay2 = false;

  SystemSnapshot sys;
  if (!copySystemSnapshot(sys)) {
    forceRelaysOff();
    return;
  }

  dhtFailCount = sensor.dhtOk ? 0 : saturatingInc(dhtFailCount);
  ultrasonicFailCount = sensor.distanceOk ? 0 : saturatingInc(ultrasonicFailCount);

  bool sensorFault = false;
  String faultReason;
  if (dhtFailCount >= 5) { sensorFault = true; faultReason = "DHT11 failed 5 times"; }
  if (ultrasonicFailCount >= 5) {
    sensorFault = true;
    if (faultReason.length() > 0) faultReason += "; ";
    faultReason += "HC-SR04 timeout 5 times";
  }

  const bool instantOccupied = sensor.distanceOk && sensor.distanceCm > 0 && sensor.distanceCm <= OCCUPIED_DISTANCE_CM;
  if (instantOccupied) { lastOccupiedMs = millis(); hasEverSeenOccupancy = true; }
  const bool occupiedHeld = instantOccupied || (hasEverSeenOccupancy && ((millis() - lastOccupiedMs) < UNOCCUPIED_TIMEOUT_MS));

  if (sensor.dhtOk) {
    if (sensor.temperatureC >= TEMP_ALERT_ON_C) temperatureAlertLatched = true;
    else if (sensor.temperatureC <= TEMP_ALERT_OFF_C) temperatureAlertLatched = false;
  }

  sys.occupied = occupiedHeld;
  sys.temperatureAlert = temperatureAlertLatched;
  sys.faultReason = "";
  sys.timestampMs = millis();

  if (sensorFault) {
    sys.state = State::FAULT;
    sys.faultReason = faultReason;
    sys.relay1On = false; sys.relay2On = false;
  } else if (sys.mode == Mode::MANUAL) {
    sys.state = State::MANUAL_OVERRIDE;
  } else if (sys.mode == Mode::AWAY) {
    sys.relay1On = false;
    sys.relay2On = instantOccupied;
    sys.state = instantOccupied ? State::ALERT : State::AUTO_MONITORING;
  } else {
    sys.state = temperatureAlertLatched ? State::ALERT : State::AUTO_MONITORING;
    sys.relay1On = sensor.lightIsDark && occupiedHeld;
    sys.relay2On = temperatureAlertLatched;
  }

  applyRelays(sys.relay1On, sys.relay2On);
  if (sys.state != previousState) { logEvent("State changed to " + String(stateName(sys.state))); previousState = sys.state; }
  if (sys.relay1On != previousRelay1) { logEvent(String("Relay 1 ") + (sys.relay1On ? "ON" : "OFF")); previousRelay1 = sys.relay1On; }
  if (sys.relay2On != previousRelay2) { logEvent(String("Relay 2 ") + (sys.relay2On ? "ON" : "OFF")); previousRelay2 = sys.relay2On; }
  if (!updateSystemSnapshot(sys)) forceRelaysOff();
}

bool setMode(Mode newMode) {
  SystemSnapshot sys;
  if (!copySystemSnapshot(sys)) return false;
  sys.mode = newMode;
  if (newMode == Mode::MANUAL) sys.state = State::MANUAL_OVERRIDE;
  sys.timestampMs = millis();
  if (!updateSystemSnapshot(sys)) return false;
  logEvent("Mode changed to " + String(modeName(newMode)));
  return true;
}

bool setManualRelay(uint8_t relayNumber, bool on) {
  SystemSnapshot sys;
  if (!copySystemSnapshot(sys)) return false;
  sys.mode = Mode::MANUAL;
  sys.state = State::MANUAL_OVERRIDE;
  if (relayNumber == 1) sys.relay1On = on;
  else if (relayNumber == 2) sys.relay2On = on;
  else return false;
  sys.timestampMs = millis();
  applyRelays(sys.relay1On, sys.relay2On);
  if (!updateSystemSnapshot(sys)) return false;
  logEvent("Manual Relay " + String(relayNumber) + " " + String(on ? "ON" : "OFF"));
  return true;
}
