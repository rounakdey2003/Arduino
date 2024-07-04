#include <DHT.h>
const int buzzer = 9;

#define sensor    A0 
#define DHTPIN 2          
#define DHTTYPE DHT11     

int gasLevel = 0;         
String quality =""; 
DHT dht(DHTPIN, DHTTYPE);


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
  Serial.println("Failed!");
    return;
  }
}

void air_sensor()
{
  gasLevel = digitalRead(sensor);
  Serial.println(gasLevel);

  if(gasLevel == 0)
      digitalWrite(buzzer, LOW);
  else{
  quality = "!!";
  digitalWrite(buzzer, HIGH);
  delay(500);        
}
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor,INPUT);
  dht.begin();
}    
}

void loop() {
air_sensor();
sendSensor(); 
}
