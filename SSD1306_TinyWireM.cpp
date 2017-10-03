#include <TinyWireM.h>

#include "SSD1306_TinyWireM.h"
#include "font6x8.h"

SSD1306::SSD1306(uint8_t address) {
  _address = address;
}

void SSD1306::begin() {
  writeCommand(SSD1306_DISPLAYOFF);
  writeCommand(SSD1306_SETDISPLAYCLOCKDIV,0x80);
  writeCommand(SSD1306_SETMULTIPLEX,SSD1306_LCDHEIGHT - 1);
  writeCommand(SSD1306_SETDISPLAYOFFSET,0x00);
  writeCommand(SSD1306_SETSTARTLINE | 0x0);
  writeCommand(SSD1306_CHARGEPUMP,0x14);
  writeCommand(SSD1306_MEMORYMODE,0x00);
  writeCommand(SSD1306_SEGREMAP | 0x1);
  writeCommand(SSD1306_COMSCANDEC);
  writeCommand(SSD1306_SETCOMPINS,0x12);
  writeCommand(SSD1306_SETCONTRAST,0xCF);
  writeCommand(SSD1306_SETPRECHARGE,0xF1);
  writeCommand(SSD1306_SETVCOMDETECT,0x40);
  writeCommand(SSD1306_DISPLAYALLON_RESUME);
  writeCommand(SSD1306_NORMALDISPLAY);
  writeCommand(SSD1306_DEACTIVATE_SCROLL);
  writeCommand(SSD1306_DISPLAYON);
  writeCommand(SSD1306_COLUMNADDR,0,SSD1306_LCDWIDTH-1);
  writeCommand(SSD1306_PAGEADDR,0,7);

  _x = 0;
  _y = 0;
}


void SSD1306::fill (uint8_t pattern)
{
  _x=0;
  _y=0;
  setPos(_x,_y);

  digitalWrite(PB3,HIGH);

  int8_t index = 0;
  for (uint16_t i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
    // send a bunch of data in one xmission
    TinyWireM.beginTransmission(_address);
    TinyWireM.write(0x40);
    for (uint8_t x=0; x<16; x++) {
      TinyWireM.write(pattern);
      i++;
    }
    TinyWireM.endTransmission(1);
    i--;
  }

  digitalWrite(PB3,LOW);

  setPos(_x,_y);
}

void SSD1306::setPos(uint8_t x, uint8_t y)
{
  _x=x;
  _y=y;

  writeCommand((x >> 4) | 0x10, x & 0x0f);
  writeCommand(0xb0 + y);
}

void SSD1306::drawText(char* text) {
  while (*text!=0) {
    drawChar(*text++);
  }
}

void SSD1306::drawChar (char c)
{
  setPos(_x,_y);

  digitalWrite(PB3,HIGH);

  TinyWireM.beginTransmission(_address);
  TinyWireM.write(0x40);
  int16_t index = (c - ' ') * 6;
  for (uint16_t i=0; i<6; i++) {
    // send a bunch of data in one xmission
    //TinyWireM.write(pgm_read_byte(&ssd1306xled_font6x8[index]));
    TinyWireM.write(pgm_read_byte(&ssd1306xled_font6x8[index++]));
  }

  TinyWireM.endTransmission(1);

  _x+=6;
  if (_x>128-12) {
    _x=0;
    _y=(_y+1)%8;
  }

  digitalWrite(PB3,LOW);
}



void SSD1306::writeCommand(uint8_t command) {
  uint8_t result;

  digitalWrite(PB3,HIGH);
  TinyWireM.beginTransmission(_address);
  TinyWireM.write(0x00);
  TinyWireM.write(command);
  result=TinyWireM.endTransmission(1);

  if (result==0) {
    digitalWrite(PB3,LOW);
  }
}

void SSD1306::writeCommand(uint8_t command,uint8_t arg1) {
  uint8_t result;

  digitalWrite(PB3,HIGH);
  TinyWireM.beginTransmission(_address);
  TinyWireM.write(0x00);
  TinyWireM.write(command);
  TinyWireM.write(arg1);
  result=TinyWireM.endTransmission(1);

  if (result==0) {
    digitalWrite(PB3,LOW);
  }
}

void SSD1306::writeCommand(uint8_t command,uint8_t arg1,uint8_t arg2) {
  uint8_t result;

  digitalWrite(PB3,HIGH);
  TinyWireM.beginTransmission(_address);
  TinyWireM.write(0x00);
  TinyWireM.write(command);
  TinyWireM.write(arg1);
  TinyWireM.write(arg2);
  result=TinyWireM.endTransmission(1);

  if (result==0) {
    digitalWrite(PB3,LOW);
  }
}
