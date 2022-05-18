#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "HUAWEI-010R2C";   // ssid
const char* password = "1992Love";    // password
const int relayPin = 0;

bool relayStatus = true;

ESP8266WebServer server(80);

void switchRelayON() {
  relayStatus = false;
  digitalWrite(relayPin, relayStatus);
  server.send(200, "text/plain", "Relay ON!");
}
void switchRelayOFF() {
  relayStatus = true;
  digitalWrite(relayPin, relayStatus);
  server.send(200, "text/plain", "Relay OFF!");
}
void sendRelayStatus() {
  server.send(200, "text/plain", "Relay status: " + String(!relayStatus));
}

void setup() {

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayStatus);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(3000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/on", switchRelayON);
  server.on("/off", switchRelayOFF);
  server.on("/status", sendRelayStatus);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {

  server.handleClient();


}

