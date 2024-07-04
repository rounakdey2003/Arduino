// Include necessary libraries
#include <ESP8266WiFi.h>
#include <NewPing.h>

// Define WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Define pin numbers for LEDs
const int redLed1 = D1; // GPIO5
const int greenLed1 = D2; // GPIO4
const int redLed2 = D5; // GPIO14
const int greenLed2 = D6; // GPIO12

// Define pin numbers for Ultrasonic sensors
const int pingSonar1 = D7; // GPIO13
const int echoSonar1 = D8; // GPIO15
const int pingSonar2 = D3; // GPIO0
const int echoSonar2 = D4; // GPIO2

// Create instances of NewPing for each sensor
NewPing sonar1(pingSonar1, echoSonar1, 200); // Max distance 200cm
NewPing sonar2(pingSonar2, echoSonar2, 200);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set pin modes for LEDs
  pinMode(redLed1, OUTPUT);
  pinMode(greenLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(greenLed2, OUTPUT);
}

void loop() {
  // Measure distances from both sensors
  int distance1 = sonar1.ping_cm();
  int distance2 = sonar2.ping_cm();

  // Control LEDs based on distance comparison
  if (distance1 >= distance2) {
    digitalWrite(redLed1, LOW);
    digitalWrite(greenLed2, LOW);
    digitalWrite(redLed2, LOW);
    digitalWrite(greenLed1, LOW);
    delay(200);
    while (distance1 > distance2) {
      distance1 = sonar1.ping_cm();
      distance2 = sonar2.ping_cm();
      digitalWrite(redLed1, HIGH);
      digitalWrite(greenLed2, HIGH);
      digitalWrite(redLed2, LOW);
      digitalWrite(greenLed1, LOW);
    }
  }

  if (distance2 > distance1) {
    digitalWrite(redLed1, LOW);
    digitalWrite(greenLed2, LOW);
    digitalWrite(redLed2, LOW);
    digitalWrite(greenLed1, LOW);
    delay(200);
    while (distance2 > distance1) {
      distance1 = sonar1.ping_cm();
      distance2 = sonar2.ping_cm();
      digitalWrite(redLed1, LOW);
      digitalWrite(greenLed2, LOW);
      digitalWrite(redLed2, HIGH);
      digitalWrite(greenLed1, HIGH);
    }
  }
}
