const int relayPin = 13;  
const int ldrPin = A0;  


void setup() {

  Serial.begin(9600);
  pinMode(relayPin, OUTPUT); 
  pinMode(ldrPin, INPUT);   
}

void loop() {

  int ldrStatus = analogRead(ldrPin);  
  

   if (ldrStatus <=400) {

    digitalWrite(relayPin, LOW);               
    Serial.println("LDR is DARK, LED is ON");
    
   }
  else {

    digitalWrite(relayPin, HIGH);         
    Serial.println("---------------");
  }
}