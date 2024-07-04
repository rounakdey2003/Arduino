#include <Adafruit_SSD1306.h>

#include <Adafruit_GFX.h>

#include <gfxfont.h>

 

#include <SPI.h> 

#include <Wire.h> 

 

#define OLED_RESET 11 

Adafruit_SSD1306 display(OLED_RESET); 

 

int led = 10; 

int buzzer = 9; 

int gas_sensor = A0; 

float m = -0.318; 

float b = 1.133; 

float R0 = 11.820; 

 

void setup() {

  Serial.begin(9600); 

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 

  display.setTextColor(WHITE);

  display.setTextSize(3); 

  pinMode(led, OUTPUT);

  digitalWrite(led, LOW); 

  pinMode(buzzer, OUTPUT); 

  digitalWrite(buzzer, LOW); 

  pinMode(gas_sensor, INPUT); 

}

 

void loop() {

  display.clearDisplay(); 

  display.setCursor(0, 5); 

  float sensor_volt; 

  float RS_gas; 

  float ratio; 

  float sensorValue = analogRead(gas_sensor); 

  sensor_volt = sensorValue * (5.0 / 1023.0); 

  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0; 

  ratio = RS_gas / R0;   

 

  double ppm_log = (log10(ratio) - b) / m; 

  double ppm = pow(10, ppm_log); 

  double percentage = ppm / 10000; 

  display.print(percentage); 

  display.print("%"); 

  display.display(); 

 

  if (ppm > 2000) {

  

    digitalWrite(led, HIGH); 

    digitalWrite(buzzer, HIGH); 

  } else {

    

    digitalWrite(led, LOW);

    
    digitalWrite(buzzer, LOW);

    

}}
