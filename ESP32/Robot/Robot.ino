#include <SCServo.h>
#include <WiFi.h>
#include "WiFiUpravljanje.h"
#include "RadMotora.h"
#include "ObradaPodataka.h"
#include "GlobalnePromenljive.h"

void setup() {
  Serial.begin(115200);
  Serial2.begin(1000000, SERIAL_8N1, 16, 17);
  servo.pSerial = &Serial2;
  WiFiSetup();
  delay(1000);
}

void loop() {
  WiFiPrijem();
}
