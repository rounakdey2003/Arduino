#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Auth Token
char auth[] = "6x0dJCUcqu3IFweJW5BL5546G7cVhDTD";

// WiFi credentials.
// Password
char ssid[] = "safeguard";
char pass[] = "safeguard";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

