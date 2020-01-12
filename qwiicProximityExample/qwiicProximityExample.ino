#include <Wire.h>
#include <SFE_MicroOLED.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"

#define PIN_RESET 9
#define DC_JUMPER 1

MicroOLED oled(PIN_RESET, DC_JUMPER);
VCNL4040 proximitySensor;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  oled.begin();
  proximitySensor.begin();
  proximitySensor.powerOnAmbient();
  proximitySensor.powerOnProximity();
  oled.clear(ALL);
  oled.clear(PAGE);
  oled.setFontType(0);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
oled.clear(PAGE);
oled.setCursor(0,0);
oled.print("prox: ");
oled.setCursor(0, oled.getFontHeight());
oled.print(proximitySensor.getProximity());
oled.setCursor(0, oled.getFontHeight()*2);
oled.print("light: ");
oled.setCursor(0, oled.getFontHeight()*3);
oled.print(proximitySensor.getAmbient());
oled.display();
}
