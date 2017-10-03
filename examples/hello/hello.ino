#include <TinyWireM.h>
#include <USI_TWI_Master.h>

#include "SSD1306_TinyWireM.h"

SSD1306 display(0x3c);

void setup() {
  pinMode(PB3,OUTPUT);
  TinyWireM.begin();
  display.begin();

  digitalWrite(PB3,HIGH);
  delay(500);
  digitalWrite(PB3,LOW);
  delay(500);
  digitalWrite(PB3,HIGH);
  delay(500);
  digitalWrite(PB3,LOW);

  display.fill(0x00);

  display.drawText("Hello world! ");
  display.drawText("Hello world! ");
  display.drawText("Hello world! ");
  display.drawText("Hello world! ");
}

void loop() {
}
