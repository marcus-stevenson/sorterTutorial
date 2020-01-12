#include <Wire.h>
#include <SFE_MicroOLED.h>
#include <SparkFun_MMA8452Q.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"

#define PIN_RESET 9
#define DC_JUMPER 1

MicroOLED oled(PIN_RESET, DC_JUMPER);
VCNL4040 proximitySensor;
MMA8452Q accel;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  proximitySensor.begin();
  proximitySensor.powerOnAmbient();
  accel.begin();
  oled.begin();
  oled.clear(ALL);
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.print("Ready");
  oled.display();
}
int clearMarbles = 0;
int blackMarbles = 0;
int sortErrors = 0;

void resetMachine(){
  while (abs(accel.getCalculatedX())>0.08){
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print("reset");
    oled.setCursor(0, oled.getFontHeight());
    oled.print("dial");
    oled.display();
  }
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print("Ready");
  oled.display();
  }
void showTotals() {
  delay(3000);
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0, 0);
  oled.print("solid: ");
  oled.print(blackMarbles);
  oled.setCursor(0, oled.getFontHeight());
  oled.print("clear: ");
  oled.print(clearMarbles);
  oled.setCursor(0, oled.getFontHeight()*2);
  oled.print("Err: ");
  oled.print(sortErrors);
  oled.display();
  oled.setFontType(1);
  delay(3000);
}
void checkSort(bool color) {
  while (abs(accel.getCalculatedX()) < 0.3) {
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print("waiting");
    oled.display();
  }
  if (color == false) {
    if (accel.getCalculatedX() < 0) {
      oled.clear(PAGE);
      oled.setCursor(0, 0);
      oled.print("correct sort");
      oled.display();
      blackMarbles ++;
      showTotals();
      resetMachine();
    } else {
      oled.clear(PAGE);
      oled.setCursor(0, 0);
      oled.print("incorrect sort");
      oled.display();
      sortErrors ++;
      showTotals();
      resetMachine();
    }
  } else {
    if (accel.getCalculatedX() > 0) {
      oled.clear(PAGE);
      oled.setCursor(0, 0);
      oled.print("correct sort");
      oled.display();
      clearMarbles ++;
      showTotals();
      resetMachine();
    } else {
      oled.clear(PAGE);
      oled.setCursor(0, 0);
      oled.print("incorrect sort");
      oled.display();
      sortErrors ++;
      showTotals();
      resetMachine();
    }
  }
}
void measureAmbLight() {
  if (proximitySensor.getAmbient() < 150) {
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print("Black Marble");
    oled.display();
    delay(2000);
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print("Sort");
    oled.setCursor(0, oled.getFontHeight());
    oled.print("Left");
    oled.display();
    checkSort(false);
  } else {
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print("Clear Marble");
    oled.display();
    delay(2000);
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    oled.print("Sort");
    oled.setCursor(0, oled.getFontHeight());
    oled.print("Right");
    oled.display();
    checkSort(true);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  oled.setCursor(0, 0);
  if (proximitySensor.getProximity() > 25) {
    oled.print("Marble Detected");
    oled.display();
    delay(1000);
    measureAmbLight();
  }
}
