#include <Arduino.h>

#include "app_state.h"
#include "control.h"
#include "sensors.h"
#include "tasks.h"
#include "web_routes.h"
#include "wifi_manager.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  setupPins();
  if (!initAppState()) {
    forceRelaysOff();
    Serial.println("Critical fault: mutex creation failed");
    return;
  }

  initSensors();
  logEvent("BOOT started");

  connectWiFiOrStartAP();
  setupWebServer();
  logEvent("Web server started");

  if (startAppTasks()) logEvent("Tasks created");
}

void loop() {
  delay(1000);
}
