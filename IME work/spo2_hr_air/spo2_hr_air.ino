#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define relayPin 13  
#define ldrPin A1
#define buzzer 9
#define sensor A0 
#define DHTPIN 2          
#define DHTTYPE DHT11
#define ENABLE_MAX30100 1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#if ENABLE_MAX30100
#define REPORTING_PERIOD_MS 5000
PulseOximeter pox;
#endif
uint32_t tsLastReport = 0;
int xPos = 0;

int gasLevel = 0;                
String quality ="";             
DHT dht(DHTPIN, DHTTYPE);      

void sendSensor()                               // temp/humidity sense korar jonno
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
  Serial.println("Failed!");
    return;
  }
}

void air_sensor()                               // methane gas sense korar jonno
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

void ldr_sensor(){                              // light er intensity sence korar jonno

 int ldrStatus = analogRead(ldrPin);             
  

   if (ldrStatus <=400) {

    digitalWrite(relayPin, LOW);               
    Serial.println("LDR Off");
    
   }
    else {

    digitalWrite(relayPin, HIGH);         
    Serial.println("LDR on");
  }    
}

void onBeatDetected()
{
  Serial.println("Beat!");
  heart_beat(&xPos);
}
void setup()
{

  Serial.begin(9600);
  pinMode(relayPin, OUTPUT); 
  pinMode(ldrPin, INPUT);   

  Serial.begin(9600);             
  pinMode(buzzer, OUTPUT);      
  pinMode(sensor,INPUT);        
  dht.begin();                  
  
  Serial.begin(115200);
  Serial.println("SSD1306 128x64 OLED TEST");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 18);
  display.print("Pulse OxiMeter");
  int temp1 = 0;
  int temp2 = 40;
  int temp3 = 80;
  heart_beat(&temp1);
  heart_beat(&temp2);
  heart_beat(&temp3);
  xPos = 0;
  display.display();
  delay(2000);
  display.cp437(true);
  display.clearDisplay();
  Serial.print("Initializing pulse oximeter..");
#if ENABLE_MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
  display_data(0, 0);
#endif
}
void loop()
{
    
  ldr_sensor();  
  air_sensor();                                               
  sendSensor();                                               

  #if ENABLE_MAX30100
  pox.update();
  int bpm = 0;
  int spo2 = 0;
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    bpm = pox.getHeartRate();
    spo2 = pox.getSpO2();
    Serial.println(bpm);
    Serial.println(spo2);
    tsLastReport = millis();
    display_data(bpm, spo2);
  }
#endif
  drawLine(&xPos);
}
void display_data(int bpm, int spo2) {          // oled e bpm/spo2 display korar jonno
 
  display.fillRect(0, 18, 127, 15, BLACK);
  display.fillRect(0, 18, 127, 15, BLACK);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 18);
  display.print("BPM ");
  display.setTextSize(2);
  display.print(bpm);
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64, 18);
  display.print("Spo2% ");
  display.setTextSize(2);
  display.println(spo2);
  display.display();
}
void drawLine(int *x_pos) {                     // oled e line display korar jonno, (pixel wise)
  
  display.drawPixel(*x_pos, 8, WHITE);
  display.drawPixel((*x_pos)++, 8, WHITE);
  display.drawPixel((*x_pos)++, 8, WHITE);
  display.drawPixel((*x_pos)++, 8, WHITE);
  display.drawPixel((*x_pos), 8, BLACK); 
  display.fillRect(*x_pos, 0, 31, 16, BLACK);
  display.display();
  if (*x_pos >= SCREEN_WIDTH) {
    *x_pos = 0;
  }
}
void heart_beat(int *x_pos) {                   // oled e heart beat display korar jonno, (pixel wise)
 
  display.fillRect(*x_pos, 0, 30, 15, BLACK);
  display.drawPixel(*x_pos + 0, 8, WHITE);
  display.drawPixel(*x_pos + 1, 8, WHITE);
  display.drawPixel(*x_pos + 2, 8, WHITE);
  display.drawPixel(*x_pos + 3, 8, WHITE);
  display.drawPixel(*x_pos + 4, 8, BLACK); 
  display.drawPixel(*x_pos + 5, 7, WHITE);
  display.drawPixel(*x_pos + 6, 6, WHITE);
  display.drawPixel(*x_pos + 7, 7, WHITE); 
  display.drawPixel(*x_pos + 8, 8, WHITE);
  display.drawPixel(*x_pos + 9, 8, WHITE); 
  display.drawPixel(*x_pos + 10, 8, WHITE);
  display.drawPixel(*x_pos + 10, 9, WHITE);
  display.drawPixel(*x_pos + 11, 10, WHITE);
  display.drawPixel(*x_pos + 11, 11, WHITE);
  display.drawPixel(*x_pos + 12, 10, WHITE);
  display.drawPixel(*x_pos + 12, 9, WHITE);
  display.drawPixel(*x_pos + 12, 8, WHITE);
  display.drawPixel(*x_pos + 12, 7, WHITE);
  display.drawPixel(*x_pos + 13, 6, WHITE);
  display.drawPixel(*x_pos + 13, 5, WHITE);
  display.drawPixel(*x_pos + 13, 4, WHITE);
  display.drawPixel(*x_pos + 13, 3, WHITE);
  display.drawPixel(*x_pos + 14, 2, WHITE);
  display.drawPixel(*x_pos + 14, 1, WHITE);
  display.drawPixel(*x_pos + 14, 0, WHITE);
  display.drawPixel(*x_pos + 14, 0, WHITE);
  display.drawPixel(*x_pos + 15, 0, WHITE);
  display.drawPixel(*x_pos + 15, 1, WHITE);
  display.drawPixel(*x_pos + 15, 2, WHITE);
  display.drawPixel(*x_pos + 15, 3, WHITE);
  display.drawPixel(*x_pos + 15, 4, WHITE);
  display.drawPixel(*x_pos + 15, 5, WHITE);
  display.drawPixel(*x_pos + 16, 6, WHITE);
  display.drawPixel(*x_pos + 16, 7, WHITE);
  display.drawPixel(*x_pos + 16, 8, WHITE);
  display.drawPixel(*x_pos + 16, 9, WHITE);
  display.drawPixel(*x_pos + 16, 10, WHITE);
  display.drawPixel(*x_pos + 16, 11, WHITE);
  display.drawPixel(*x_pos + 17, 12, WHITE);
  display.drawPixel(*x_pos + 17, 13, WHITE);
  display.drawPixel(*x_pos + 17, 14, WHITE);
  display.drawPixel(*x_pos + 17, 15, WHITE);
  display.drawPixel(*x_pos + 18, 15, WHITE);
  display.drawPixel(*x_pos + 18, 14, WHITE);
  display.drawPixel(*x_pos + 18, 13, WHITE);
  display.drawPixel(*x_pos + 18, 12, WHITE);
  display.drawPixel(*x_pos + 19, 11, WHITE);
  display.drawPixel(*x_pos + 19, 10, WHITE);
  display.drawPixel(*x_pos + 19, 9, WHITE);
  display.drawPixel(*x_pos + 19, 8, WHITE);
  display.drawPixel(*x_pos + 20, 8, WHITE);
  display.drawPixel(*x_pos + 21, 8, WHITE);
  display.drawPixel(*x_pos + 22, 7, WHITE);
  display.drawPixel(*x_pos + 23, 6, WHITE);
  display.drawPixel(*x_pos + 24, 6, WHITE);
  display.drawPixel(*x_pos + 25, 7, WHITE);
  display.drawPixel(*x_pos + 26, 8, WHITE);
  display.drawPixel(*x_pos + 27, 8, WHITE);
  display.drawPixel(*x_pos + 28, 8, WHITE);
  display.drawPixel(*x_pos + 29, 8, WHITE);
  display.drawPixel(*x_pos + 30, 8, WHITE);
  *x_pos = *x_pos + 30;
  display.display();
  delay(1);
}