#include<UltraDistSensor.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include <Adafruit_MLX90614.h>

#define OLED_RESET 4

UltraDistSensor mysensor;
float reading;

Adafruit_SSD1306 display(OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()  
{               
  Serial.begin(57600);
  Serial.println("Adafruit MLX90614 test"); 
  mlx.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  mysensor.attach(12,13);
}


void loop()
{    

  reading=mysensor.distanceInCm();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.print(" Maintain 90cm");
  display.setCursor(0,10);
  display.print(reading);
  display.print("cm");
     
  display.setCursor(0,20);
  display.print("Ambient: ");
  display.print(mlx.readAmbientTempC());
  display.print(" c");
  display.setCursor(0,30);
  display.print("Object: ");
  display.print(mlx.readObjectTempC());
  display.print(" c");
  display.display();
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
  
  delay(2000);

}
