#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"
#define ACTIVE LOW



int state = 0;
const int pin = 9;
float gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);

void setup()
{
  sgsm.begin(9600);
  sgps.begin(9600);

  Serial.begin(9600);
    pinMode(ledPin,OUTPUT);
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin,HIGH);
    if (gsm.begin(9600)) 
    {
        Serial.println("\nstatus=READY");
        started=true;   
    } 
    else 
        Serial.println("\nstatus=IDLE");
}

void loop()
{
sgps.listen();
  while (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
    if (digitalRead(pin) == HIGH && state == 0) {
      sgsm.listen();
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      sgsm.print("AT+CMGS=\"+91XXXXXXXXXX\"\r");
      delay(1000);
      sgsm.print("Latitude :");
      sgsm.println(gpslat, 6);
      sgsm.print("Longitude:");
      sgsm.println(gpslon, 6);
      delay(1000);
      sgsm.write(0x1A);
      delay(1000);
      state = 1;
    }
  if (digitalRead(pin) == LOW) {
      state = 0;
    }
      delay(1000);

      buttonState = digitalRead(buttonPin);
  if (buttonState == ACTIVE) {
     if(calling)
     {
      digitalWrite(ledPin,LOW);
      calling = false;
      call.HangUp();
      delay(1000);
      }else
     {
      calling = true;
      digitalWrite(ledPin, HIGH);
      delay(1000);
      call.Call("+300000000000"); 
  }


//#include "SIM900.h"
//#include <SoftwareSerial.h>
//#include "call.h"

//#define ACTIVE LOW

//const int ledPin =  13;      
//
//CallGSM call;
//boolean started=false;
//int buttonState = 1;    
//const int buttonPin = 7;    
//boolean calling = false;

void setup()
{
  
  Serial.begin(9600);
    pinMode(ledPin,OUTPUT);
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin,HIGH);
    if (gsm.begin(9600)) 
    {
        Serial.println("\nstatus=READY");
        started=true;   
    } 
    else 
        Serial.println("\nstatus=IDLE");
}

//void loop()
//{
//buttonState = digitalRead(buttonPin);
//if (buttonState == ACTIVE) {
//     if(calling)
//     {
//      digitalWrite(ledPin,LOW);
//      calling = false;
//      call.HangUp();
//      delay(1000);
//      }else
//     {
//      calling = true;
//      digitalWrite(ledPin, HIGH);
//      delay(1000);
//      call.Call("+300000000000"); 
//  
//}
