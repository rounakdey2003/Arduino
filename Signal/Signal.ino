int redLed1=5;
int greenLed1=6;
// int redLed3
// int redLed4

int redLed2=7;
int greenLed2=8;
// int greenLed3
// int greenLed4

const int pingSonar1=9;
const int echoSonar1=10;

const int pingSonar2=11;
const int echoSonar2=12;

// const int pingSonar3
// const int echoSonar3

// const int pingSonar4
// const int echoSonar4


void setup() {
  
  pinMode(redLed1,OUTPUT);
  pinMode(redLed2,OUTPUT);

  pinMode(greenLed1,OUTPUT);
  pinMode(greenLed2,OUTPUT);

}

void loop() {
  
  int distance1,distance2;

  distance1=calculatedistance(pingSonar1 , echoSonar1);
  distance2=calculatedistance(pingSonar2 , echoSonar2);

  if(distance1>=distance2){

    digitalWrite(redLed1,LOW);
    digitalWrite(greenLed2,LOW);
    digitalWrite(redLed2,LOW);
    digitalWrite(greenLed1,LOW);
    
    delay(200);

    while(distance1>distance2){

          distance1=calculatedistance(pingSonar1 , echoSonar1);
          distance2=calculatedistance(pingSonar2 , echoSonar2);


          digitalWrite(redLed1,HIGH);
          digitalWrite(greenLed2,HIGH);
          digitalWrite(redLed2,LOW);
          digitalWrite(greenLed1,LOW);
        
    }

  }

if(distance2>distance1){

  digitalWrite(redLed1,LOW);
  digitalWrite(greenLed2,LOW);
  digitalWrite(redLed2,LOW);
  digitalWrite(greenLed1,LOW);

  delay(200);

  while(distance2>distance1){
    
        distance1=calculatedistance(pingSonar1 , echoSonar1);
        distance2=calculatedistance(pingSonar2 , echoSonar2);

        digitalWrite(redLed1,LOW);
        digitalWrite(greenLed2,LOW);
        digitalWrite(redLed2,HIGH);
        digitalWrite(greenLed1,HIGH);
        
  }

}

}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}

int calculatedistance(int pingSonar1 , int echoSonar1){
  long duration, inches, cm,meter;

  pinMode(pingSonar1, OUTPUT);
  digitalWrite(pingSonar1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingSonar1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingSonar1, LOW);

  pinMode(echoSonar1, INPUT);
  duration = pulseIn(echoSonar1, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  meter = cm/100;
  return meter;

}
