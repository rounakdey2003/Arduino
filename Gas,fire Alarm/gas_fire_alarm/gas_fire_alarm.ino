#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>;

#define DHTPIN = 14; // D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int lm393 = A3;  
int mq07 = A0; 
int mq04 = A1; 
int buzzer = 12; // D6

int carbon;
int methane;
int flame;
int temp;

char auth[] = "Auth Token";
char ssid[] = "WiFi SSID"; 
char pass[] = "WiFi Password";
/////coded by Rounak Dey////
void setup()
{
  pinMode(lm393, INPUT);
  pinMode(mq07, INPUT);
  pinMode(mq04, INPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(buzzer, LOW);
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() 
{ 
  flame = digitalRead(lm393); 
  Blynk.virtualWrite(V0, flame); 
  Serial.print("Flame Status:");
  Serial.println(flame);
  
 if (flame == avg num)
    {
    digitalWrite(buzzer, HIGH);
    Blynk.notify("Alert!!! Fire Detected");  
    }
  else
    {
      digitalWrite(buzzer, LOW);
    }

  temp = dht.readTemperature();
  Blynk.virtualWrite(V2, temp);
  Serial.print("Temperature Level:");
  Serial.println(temp);
  Serial.print("%");

  if (temp > avg num)
    {
    digitalWrite(buzzer, HIGH);
    Blynk.notify("Alert!!! Temperature rising");  
    }
  else
    {
     digitalWrite(buzzer, LOW);
    }

  carbon = analogRead(mq07);
  Blynk.virtualWrite(V3, carbon);
  Serial.print("CO Gas Level:");
  Serial.println(carbon);

  if (carbon > avg num)
    {
    digitalWrite(buzzer, HIGH);
    Blynk.notify("Alert!!! Smoke Detected");  
    }
  else
    {
     digitalWrite(buzzer, LOW);
    }

  methane = analogRead(mq04);
  Blynk.virtualWrite(V4, methane);
  Serial.print("Methane Gas Level:");
  Serial.println(methane);

  if (methane > avg num)
    {
    digitalWrite(buzzer, HIGH);
    Blynk.notify("Alert!!! Gas Leakage");  
    }
  else
    {
     digitalWrite(buzzer, LOW);
    }
    
  delay(500);
  Blynk.run();
}
