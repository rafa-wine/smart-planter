#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "sleep.h"
#include "yawn.h"
#include "normal.h"
#include "vampire.h"
#include "sick.h"
#include "lowTemperature.h"
#include "highTemperature.h"
#include "drySoil.h"
#include "veryWetSoil.h"

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

// create an OLED display object connected to I2C
Adafruit_SSD1306 oledDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void startDisplay() {
  // initialize OLED display with I2C address 0x3C
  if (!oledDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  delay(2000);         // wait two seconds for initializing
  oledDisplay.clearDisplay(); // clear display
  oledDisplay.setTextSize(1);         // set text size
  oledDisplay.setTextColor(WHITE);    // set text color
  oledDisplay.setCursor(0, 0);       // set position to display
  oledDisplay.cp437(true);
}

void welcomeAnimation() {
  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(2);
  oledDisplay.setCursor(15, 0);
  oledDisplay.write(173);
  oledDisplay.print("Conecta");
  oledDisplay.setCursor(45, 21);
  oledDisplay.print("con");
  oledDisplay.setCursor(15, 42);
  oledDisplay.print("la Vida!");
  oledDisplay.display();
  delay(5000);
}

void connectToWifi() {
  oledDisplay.clearDisplay();
  oledDisplay.setTextSize(1);
  oledDisplay.setCursor(15, 30);
  oledDisplay.print("Iniciando...");
  oledDisplay.display();
  delay(1000);
}

void sleepAnimation() {
  for(int i=0; i<sleepFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, sleepArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();
     delay(75);
  }
}

void yawnAnimation() {
  for(int i=0; i<yawnFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, yawnArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();

     if(i == 4) {
       delay(600);
     }
     else {
      delay(75);  
     }
  }
}

void normalAnimation() {
  for(int i=0; i<normalFrames; i++) {     
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, normalArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();

     if(i == 18) {
       delay(3500);
     }
     else {
       delay(20);
     }      
  }
}

void vampireAnimation() {
  for (int i=0; i<vampireFrames; i++)
  {
    oledDisplay.clearDisplay();
    oledDisplay.drawBitmap(0, 0, vampireArray[i], 128, 64, SSD1306_WHITE);
    oledDisplay.display();

    if (i < 11)
    {
      delay(75);
    }
    else if (i < 26)
    {
      delay(15);
    }
    else {
      delay(40);
    }    
  }
  
}

void sickAnimation() {
  for(int i=0; i<sickFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, sickArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();
     delay(75);
  }
}

void lowTemperatureAnimation() {
  for(int i=0; i<lowTemperatureFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, lowTemperatureArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();
     delay(75);
  }
}

void highTemperatureAnimation() {
  for(int i=0; i<highTemperatureFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, highTemperatureArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();
     delay(75);
  }
}

void drySoilAnimation() {
  for(int i=0; i<drySoilFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, drySoilArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();
     delay(75);
  }
}

void veryWetSoilAnimation() {
  for(int i=0; i<veryWetSoilFrames; i++) {
     oledDisplay.clearDisplay();
     oledDisplay.drawBitmap(0, 0, veryWetSoilArray[i], 128, 64, SSD1306_WHITE);
     oledDisplay.display();
     delay(75);
  }
}