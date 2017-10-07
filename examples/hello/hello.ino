#include <TinyWireM.h>
#include <SSD1306_TinyWireM.h>

SSD1306 display(0x3c);

void setup() {
  TinyWireM.begin();
  display.begin();

  display.fill(0x00);

  display.drawText("Hello world! ");
  display.drawText("Hello world! ");
  display.drawText("Hello world! ");
  display.drawText("Hello world! ");
}

void loop() {
}
