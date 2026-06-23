#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "app_state.h"
#include "control.h"
#include "dashboard.h"
#include "web_routes.h"

namespace { WebServer server(80); }

void handleWebClient() { server.handleClient(); }

namespace {
void sendCorsHeaders() { server.sendHeader("Access-Control-Allow-Origin", "*"); }
void sendNoStoreHeaders() { server.sendHeader("Cache-Control", "no-store, max-age=0"); server.sendHeader("Pragma", "no-cache"); }
void appendJsonString(String& json, const String& value) { json += '"'; json += jsonEscape(value); json += '"'; }
void sendJson(int status, const String& payload) { sendCorsHeaders(); sendNoStoreHeaders(); server.send(status, "application/json", payload); }
void sendOk() { sendJson(200, "{\"ok\":true}"); }
void sendStateError() { sendJson(503, "{\"ok\":false,\"error\":\"state_unavailable\"}"); }

String buildStatusJson() {
  SensorSnapshot sensor;
  SystemSnapshot sys;
  const bool sensorOk = copySensorSnapshot(sensor);
  const bool systemOk = copySystemSnapshot(sys);
  if (!sensorOk || !systemOk) return "{\"ok\":false,\"error\":\"state_unavailable\"}";
  String json; json.reserve(560);
  json += "{\"temperature_c\":"; json += sensor.dhtOk ? String(sensor.temperatureC, 1) : "null";
  json += ",\"humidity\":"; json += sensor.dhtOk ? String(sensor.humidity, 1) : "null";
  json += ",\"dht_ok\":"; json += sensor.dhtOk ? "true" : "false";
  json += ",\"distance_cm\":"; json += sensor.distanceOk ? String(sensor.distanceCm) : "null";
  json += ",\"distance_ok\":"; json += sensor.distanceOk ? "true" : "false";
  json += ",\"light_is_dark\":"; json += sensor.lightIsDark ? "true" : "false";
  json += ",\"occupied\":"; json += sys.occupied ? "true" : "false";
  json += ",\"mode\":\""; json += modeName(sys.mode);
  json += "\",\"state\":\""; json += stateName(sys.state);
  json += "\",\"relay1\":"; json += sys.relay1On ? "true" : "false";
  json += ",\"relay2\":"; json += sys.relay2On ? "true" : "false";
  json += ",\"temperature_alert\":"; json += sys.temperatureAlert ? "true" : "false";
  json += ",\"fault_reason\":"; appendJsonString(json, sys.faultReason);
  json += ",\"uptime_s\":"; json += String(millis() / 1000);
  json += ",\"wifi_mode\":\""; json += (WiFi.getMode() == WIFI_AP ? "AP" : "STA");
  json += "\",\"ip\":\""; json += (WiFi.getMode() == WIFI_AP ? WiFi.softAPIP().toString() : WiFi.localIP().toString());
  json += "\",\"heap_free\":"; json += String(ESP.getFreeHeap());
  if (WiFi.getMode() == WIFI_STA && WiFi.status() == WL_CONNECTED) { json += ",\"rssi\":"; json += String(WiFi.RSSI()); }
  json += "}"; return json;
}

String buildLogsJson() {
  String events[EVENT_LOG_SIZE];
  const uint8_t count = copyEventLog(events);
  String json; json.reserve(384); json += "[";
  for (uint8_t i = 0; i < count; i++) { appendJsonString(json, events[i]); if (i < count - 1) json += ","; }
  json += "]"; return json;
}

void handleRoot() { server.sendHeader("Cache-Control", "no-store, max-age=0"); server.send_P(200, "text/html", DASHBOARD_HTML); }
void handleSetMode(Mode mode) { if (setMode(mode)) sendOk(); else sendStateError(); }
void handleRelay(uint8_t relay, bool on) { if (setManualRelay(relay, on)) sendOk(); else sendStateError(); }
}

void setupWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/status", HTTP_GET, []() { sendJson(200, buildStatusJson()); });
  server.on("/api/logs", HTTP_GET, []() { sendJson(200, buildLogsJson()); });
  server.on("/api/mode/auto", HTTP_POST, []() { handleSetMode(Mode::AUTO); });
  server.on("/api/mode/manual", HTTP_POST, []() { handleSetMode(Mode::MANUAL); });
  server.on("/api/mode/away", HTTP_POST, []() { handleSetMode(Mode::AWAY); });
  server.on("/api/relay1/on", HTTP_POST, []() { handleRelay(1, true); });
  server.on("/api/relay1/off", HTTP_POST, []() { handleRelay(1, false); });
  server.on("/api/relay2/on", HTTP_POST, []() { handleRelay(2, true); });
  server.on("/api/relay2/off", HTTP_POST, []() { handleRelay(2, false); });
  server.begin();
}
