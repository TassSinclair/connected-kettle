#include "display.h"

byte Display::_KETTLE_LEFT_TOP[8] = {
  0b00000,
  0b00001,
  0b00010,
  0b11110,
  0b01110,
  0b00110,
  0b00010,
  0b00010
};

byte Display::_KETTLE_LEFT_BOTTOM[8] = {
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00110,
  0b01111
};

byte Display::_KETTLE_RIGHT_TOP[8] = {
  0b00000,
  0b10000,
  0b01000,
  0b01100,
  0b01110,
  0b01011,
  0b01011,
  0b01011
};

byte Display::_KETTLE_RIGHT_BOTTOM[8] = {
  0b01011,
  0b01011,
  0b01011,
  0b01111,
  0b01110,
  0b01000,
  0b01100,
  0b11110
};

byte Display::_KETTLE_FILL_NONE[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
};

byte Display::_KETTLE_FILL_SOME[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
};

byte Display::_KETTLE_FILL_MORE[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
};

byte Display::_KETTLE_FILL_MOST[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
};

Display::Display(
  LiquidCrystal lcd, 
  unsigned contrast_pin,
  unsigned contrast) : _lcd(lcd), _contrast_pin(contrast_pin), _contrast(contrast)
{
}


void Display::connect()
{
  pinMode(_contrast_pin, OUTPUT);
  analogWrite(_contrast_pin, _contrast, 255);

  set_backlight(true);
  _lcd.begin(16,2);
  _lcd.createChar(0, _KETTLE_LEFT_TOP);
  _lcd.createChar(1, _KETTLE_LEFT_BOTTOM);
  _lcd.createChar(2, _KETTLE_RIGHT_TOP);
  _lcd.createChar(3, _KETTLE_RIGHT_BOTTOM);
  _lcd.createChar(4, _KETTLE_FILL_NONE);
  _lcd.createChar(5, _KETTLE_FILL_SOME);
  _lcd.createChar(6, _KETTLE_FILL_MORE);
  _lcd.createChar(7, _KETTLE_FILL_MOST);
}

void Display::clear()
{
  _lcd.clear();
}

void Display::set_backlight(bool on)
{
  _lcd.setBacklight(on ? 128 : 0);
}

void Display::print_load(float load)
{
  _lcd.setCursor(4, 1);
  _lcd.print("Load: ");
  _lcd.print(load, 2);
  _lcd.print("kg");

  print_kettle();
  print_kettle_filling(load);
}

void Display::print_temperature(float temperature)
{
  _lcd.setCursor(4, 0);
  _lcd.print("Temp: ");
  _lcd.print(temperature, 0);
  _lcd.print((char)223);
  _lcd.print("C");
}

void Display::print(const char *line_1, const char *line_2)
{
  _lcd.clear();
  _lcd.setCursor(0, 0);
  _lcd.print(line_1);
  _lcd.setCursor(0, 1);
  _lcd.print(line_2);
}

void Display::print_kettle()
{
  _lcd.setCursor(0, 0);
  _lcd.print(char(0));
  _lcd.setCursor(0, 1);
  _lcd.print(char(1));
  _lcd.setCursor(2, 0);
  _lcd.print(char(2));
  _lcd.setCursor(2, 1);
  _lcd.print(char(3));
}

void Display::print_kettle_filling(float load)
{
  if (load < 0.25)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(" ");
    _lcd.setCursor(1, 1);
    _lcd.print(char(4));
  }
  else if (load < 0.5)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(" ");
    _lcd.setCursor(1, 1);
    _lcd.print(char(5));
  }
  else if (load < 0.75)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(" ");
    _lcd.setCursor(1, 1);
    _lcd.print(char(6));
  }
  else if (load < 1)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(" ");
    _lcd.setCursor(1, 1);
    _lcd.print(char(7));
  }
  else if (load < 1.25)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(" ");
    _lcd.setCursor(1, 1);
    _lcd.print((char)255);
  }
  else if (load < 1.5)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(char(5));
    _lcd.setCursor(1, 1);
    _lcd.print((char)255);
  }
  else if (load < 1.75)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(char(6));
    _lcd.setCursor(1, 1);
    _lcd.print((char)255);
  }
  else if (load < 2)
  {
    _lcd.setCursor(1, 0);
    _lcd.print(char(7));
    _lcd.setCursor(1, 1);
    _lcd.print((char)255);
  }
  else
  {
    _lcd.setCursor(1, 0);
    _lcd.print((char)255);
    _lcd.setCursor(1, 1);
    _lcd.print((char)255);
  }
}