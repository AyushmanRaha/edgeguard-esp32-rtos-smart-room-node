#pragma once

#include "edgeguard_types.h"

const char* modeName(Mode mode);
const char* stateName(State state);
const char* faultReason(FaultCode code);
ControlConfig defaultControlConfig();
ControlResult updateControlLogic(const SensorSnapshot& sensor, const SystemSnapshot& previousSystem,
                                 ControlContext& ctx, const ControlConfig& cfg, uint32_t nowMs);
