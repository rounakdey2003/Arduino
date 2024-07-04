#include<UltraDistSensor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

LiquidCrystal_I2C lcd(0x27,20,4);

UltraDistSensor mysensor;
float reading;

void setup() {
    lcd.init();                       
    lcd.backlight();
    Serial.begin(9600);
    mlx.begin();
    mysensor.attach(12,13);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

void loop() 
{
    reading=mysensor.distanceInCm();
    if(reading < 60)
    {
     lcd.clear();
     lcd.setCursor(0,0);
     //lcd.print("Ambient = "); 
     //lcd.print(mlx.readAmbientTempC()); 
     //lcd.print("*C\tObject = "); 
     //lcd.print(mlx.readObjectTempC()); 
     //lcd.println("*C");
     lcd.print("Ambient = "); 
     lcd.print(mlx.readAmbientTempF()); 
     lcd.print("F"); 
     lcd.setCursor(0,1);
     lcd.print("Object = ");
     lcd.print(mlx.readObjectTempF()); 
     lcd.print("F");
    }
    else
    {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" Maintain 90cm");
     lcd.setCursor(4,1);
     lcd.print(reading);
     lcd.print("cm");
    }
    if(reading <= 60 && mlx.readObjectTempF() <= 98)
    {
      if(mlx.readObjectTempF() >= 87)
      {
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      delay(10000);
      }
      else
      {
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);   
      }
    }   
    delay(1000);
}
