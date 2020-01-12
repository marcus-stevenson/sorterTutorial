#include <SparkFun_MMA8452Q.h>


#include <Wire.h>
#include <SFE_MicroOLED.h>

#define PIN_RESET 9
#define DC_JUMPER 1

MicroOLED oled(PIN_RESET, DC_JUMPER);
MMA8452Q accel;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  accel.begin();
  oled.begin();
  oled.clear(ALL);
  oled.clear(PAGE);
  oled.setFontType(1);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
oled.clear(PAGE);
oled.setCursor(0,0);
oled.print("x: ");
oled.print(accel.getCalculatedX());
oled.setCursor(0, oled.getFontHeight());
oled.print("y: ");
oled.print(accel.getCalculatedY());
oled.setCursor(0, oled.getFontHeight()*2);
oled.print("z: ");
oled.print(accel.getCalculatedZ());
oled.display();

}
