#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "app_state.h"
#include "config.h"
#include "control.h"
#include "sensors.h"
#include "tasks.h"
#include "web_routes.h"

namespace {
void SensorTask(void*) {
  for (;;) {
    const SensorSnapshot reading = readSensors();
    updateSensorSnapshot(reading);
    Serial.print("T=");
    if (reading.dhtOk) { Serial.print(reading.temperatureC, 1); Serial.print("C H="); Serial.print(reading.humidity, 1); Serial.print("%"); }
    else Serial.print("DHT_ERR");
    Serial.print(" DIST=");
    if (reading.distanceOk) { Serial.print(reading.distanceCm); Serial.print("cm"); }
    else Serial.print("NO_ECHO");
    Serial.print(" LIGHT="); Serial.println(reading.lightIsDark ? "DARK" : "BRIGHT");
    vTaskDelay(pdMS_TO_TICKS(SENSOR_TASK_PERIOD_MS));
  }
}

void ControlTask(void*) {
  for (;;) {
    SensorSnapshot sensor;
    if (copySensorSnapshot(sensor)) updateControl(sensor);
    else forceRelaysOff();
    vTaskDelay(pdMS_TO_TICKS(CONTROL_TASK_PERIOD_MS));
  }
}

void WebTask(void*) { for (;;) { handleWebClient(); vTaskDelay(pdMS_TO_TICKS(10)); } }

void HeartbeatTask(void*) {
  bool ledState = false;
  for (;;) {
    SystemSnapshot sys;
    if (!copySystemSnapshot(sys)) { digitalWrite(PIN_LED_GREEN, LOW); digitalWrite(PIN_LED_RED, HIGH); vTaskDelay(pdMS_TO_TICKS(HEARTBEAT_FAULT_MS)); continue; }
    ledState = !ledState;
    if (sys.state == State::FAULT) {
      digitalWrite(PIN_LED_GREEN, LOW); digitalWrite(PIN_LED_RED, ledState ? HIGH : LOW); vTaskDelay(pdMS_TO_TICKS(HEARTBEAT_FAULT_MS));
    } else if (sys.state == State::ALERT) {
      digitalWrite(PIN_LED_GREEN, HIGH); digitalWrite(PIN_LED_RED, ledState ? HIGH : LOW); vTaskDelay(pdMS_TO_TICKS(HEARTBEAT_ALERT_MS));
    } else {
      digitalWrite(PIN_LED_RED, LOW); digitalWrite(PIN_LED_GREEN, ledState ? HIGH : LOW); vTaskDelay(pdMS_TO_TICKS(HEARTBEAT_NORMAL_MS));
    }
  }
}

bool createTask(TaskFunction_t fn, const char* name, uint32_t stack, UBaseType_t priority, BaseType_t core) {
  const BaseType_t result = xTaskCreatePinnedToCore(fn, name, stack, nullptr, priority, nullptr, core);
  if (result != pdPASS) logEvent(String("Task creation failed: ") + name);
  return result == pdPASS;
}
}

bool startAppTasks() {
  bool ok = true;
  ok &= createTask(SensorTask, "SensorTask", 4096, 2, 1);
  ok &= createTask(ControlTask, "ControlTask", 4096, 2, 1);
  ok &= createTask(WebTask, "WebTask", 8192, 1, 0);
  ok &= createTask(HeartbeatTask, "HeartbeatTask", 2048, 1, 1);
  if (!ok) { forceRelaysOff(); markCriticalFault("FreeRTOS task creation failed"); }
  return ok;
}
