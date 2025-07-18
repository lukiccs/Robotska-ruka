#include "WiFiUpravljanje.h"
#include <Arduino.h>
#include "GlobalnePromenljive.h"
#include "ObradaPodataka.h"

// const char* ssid = "Yettel_1C9368";//Beograd
// const char* password = "cT9zCSH7";

const char* ssid = "Luki _EXT";//Cacak
const char* password = "26103130";

WiFiServer serverWIFI(1234);

void WiFiSetup() {
  // Pravi i proverava povezanost preko WiFi
  WiFi.begin(ssid, password);
  Serial.print("Povezuje se...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WIFI Povezan!");
  Serial.println(WiFi.localIP());
  serverWIFI.begin();
}

void WiFiPrijem() {
  // Prima podatke iz MATLAB-a i salje ih na obradu
  WiFiClient client = serverWIFI.accept();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String poruka = client.readStringUntil('\n');
        obradaNiza(poruka);
        client.println("nastavi"); // Handshake protocol
      }
    }
    client.stop();
  }
}