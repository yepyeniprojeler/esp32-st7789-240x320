/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit ESP32-S2 TFT Feather
    ----> http://www.adafruit.com/products/5300

  Check out the links above for our tutorials and wiring diagrams.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#define TFT_CS 2
#define TFT_DC 27
#define TFT_RST 33
#define TFT_BACKLITE 15


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ST7789.h" // Hardware-specific library for ST7789
#include "ClosedCube_HDC1080.h"

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

ClosedCube_HDC1080 hdc1080;

float p = 3.1415926;

void setup(void) {

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  delay(10);

  // initialize TFT
  tft.init(240, 320,SPI_MODE2); // Init ST7789 240x320
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextWrap(false);


  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  
  uint16_t time = millis();

  time = millis() - time;

  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("HDC1080 Test");

// Default settings:
// - Heater off
// - 14 bit Temperature and Humidity Measurement Resolutions
hdc1080.begin(0x40);

  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("Manu. ID: ");

  tft.setCursor(150, 30);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(hdc1080.readManufacturerId(), HEX);



  tft.setCursor(0, 60);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("Device ID: ");

  tft.setCursor(150, 60);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(hdc1080.readDeviceId(), HEX);


  tft.setCursor(0, 90);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("SeriNo:");

  HDC1080_SerialNumber sernum = hdc1080.readSerialNumber();
  char format[20];
  sprintf(format, "%02X-%04X-%04X", sernum.serialFirst, sernum.serialMid, sernum.serialLast);

  tft.setCursor(80, 90);
  tft.setTextColor(ST77XX_WHITE);
  tft.println(format);
//tft.setTextWrap(true);
}

void loop() {
char format2[10]="";

//tft.fillRoundRect(80, 150, 200, 200, 5, ST77XX_BLACK);

  tft.setCursor(0, 150);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(3);
  tft.println("T: ");

  tft.setCursor(80, 150);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  sprintf(format2, "%03.3f C", hdc1080.readTemperature());
  tft.println(format2);
  //tft.printFloat(hdc1080.readTemperature(),6);


  tft.setCursor(0, 190);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(3);
  tft.println("RH: ");

  tft.setCursor(80, 190);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  sprintf(format2, "%03.3f %%", hdc1080.readHumidity());
  tft.println(format2);
  //tft.printFloat(hdc1080.readHumidity(),3);

  //tft.println(float(myEulerData.h) / 16.00);// declarer une fonction qui prend en compte les variables x,y et z 
    //Serial.print(" Axe z(yaw): ");       //To read out the Heading (Yaw)
    //Serial.println(float(myEulerData.h) / 16.00);   //Convert to degrees

   // Serial.print(" Axe X(Roll): ");         //To read out the Roll
   // Serial.println(float(myEulerData.r) / 16.00);   //Convert to degrees

   // Serial.print(" Axe Y (Pitch): ");        //To read out the Pitch
   // Serial.println(float(myEulerData.p ) / 16.00);   //Convert to degrees
    //Serial.println();         //Extra line to differentiate between packets

  delay(3000);
}

void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x,
                 color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x,
                 color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x,
                 color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < tft.width(); x += radius * 2) {
    for (int16_t y = radius; y < tft.height(); y += radius * 2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0; i <= 16; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}


