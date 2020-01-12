#include <SFE_MicroOLED.h>
#include <Wire.h>

#define PIN_RESET 9
#define DC_JUMPER 1

MicroOLED oled(PIN_RESET, DC_JUMPER);


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  oled.begin();
  oled.clear(ALL);
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0,0);
  oled.print("hello world!");
  oled.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(4000);
  oled.clear(PAGE);
  oled.setFontType(1);
  oled.setCursor(0,0);
  oled.print("Line 1");
  oled.setCursor(0, oled.getFontHeight());
  oled.print("Line 2 ");
  oled.setCursor(0, oled.getFontHeight()*2);
  oled.print("Line 3");
  oled.display();
  
}
