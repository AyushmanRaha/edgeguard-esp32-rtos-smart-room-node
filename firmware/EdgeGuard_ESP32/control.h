#pragma once
#include <Arduino.h>
#include "types.h"

void setupPins();
void applyRelays(bool relay1On, bool relay2On);
void forceRelaysOff();
void updateControl(const SensorSnapshot& sensor);
bool setMode(Mode newMode);
bool setManualRelay(uint8_t relayNumber, bool on);
