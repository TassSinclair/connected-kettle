#include <LiquidCrystal.h>
#include "display.h"

#include <analogWrite.h>

Display::Display(
    LiquidCrystal lcd, 
    unsigned contrastPin,
    unsigned contrast) : _lcd(lcd), _contrastPin(contrastPin), _contrast(contrast)
{
}


void Display::begin()
{
    pinMode(_contrastPin, OUTPUT);
    analogWrite(_contrastPin, _contrast, 255);

    _lcd.backlight();
    _lcd.setBacklight(128);
    _lcd.begin(16,2);
    _lcd.createChar (0, left_top);    
    _lcd.createChar (1, left_bottom); 
    _lcd.createChar (2, right_top);   
    _lcd.createChar (3, right_bottom);
    _lcd.createChar (4, none);
    _lcd.createChar (5, some);
    _lcd.createChar (6, more);
    _lcd.createChar (7, most);
}

void Display::clear()
{
    _lcd.clear();
}

void Display::printLoad(float load)
{
    _lcd.setCursor (4, 1);
    _lcd.print("Load: ");
    _lcd.print(load, 2);
    _lcd.print("kg");

    printKettle();
    printKettleFilling(load);
}

void Display::printTemperature(float temperature)
{
    _lcd.setCursor(4, 0);
    _lcd.print("Temp: ");
    _lcd.print(temperature, 0);
    _lcd.print((char)223);
    _lcd.print("C");
}

void Display::print(const char *line1, const char *line2)
{
    _lcd.clear();
    _lcd.setCursor (0, 0);
    _lcd.print(line1);
    _lcd.setCursor (0, 1);
    _lcd.print(line2);
}

void Display::printKettle()
{
    _lcd.setCursor ( 0, 0 );
    _lcd.print (char(0));
    _lcd.setCursor ( 0, 1 );
    _lcd.print (char(1));
    _lcd.setCursor ( 2, 0 );
    _lcd.print (char(2));
    _lcd.setCursor ( 2, 1 );
    _lcd.print (char(3));
}

void Display::printKettleFilling(float load)
{
    if (load < 0.25)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (" ");
        _lcd.setCursor ( 1, 1 );
        _lcd.print (char(4));
    }
    else if (load < 0.5)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (" ");
        _lcd.setCursor ( 1, 1 );
        _lcd.print (char(5));
    }
    else if (load < 0.75)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (" ");
        _lcd.setCursor ( 1, 1 );
        _lcd.print (char(6));
    }
    else if (load < 1)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (" ");
        _lcd.setCursor ( 1, 1 );
        _lcd.print (char(7));
    }
    else if (load < 1.25)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (" ");
        _lcd.setCursor ( 1, 1 );
        _lcd.print ((char)255);
    }
    else if (load < 1.5)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (char(5));
        _lcd.setCursor ( 1, 1 );
        _lcd.print ((char)255);
    }
    else if (load < 1.75)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (char(6));
        _lcd.setCursor ( 1, 1 );
        _lcd.print ((char)255);
    }
    else if (load < 2)
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print (char(7));
        _lcd.setCursor ( 1, 1 );
        _lcd.print ((char)255);
    }
    else
    {
        _lcd.setCursor ( 1, 0 );
        _lcd.print ((char)255);
        _lcd.setCursor ( 1, 1 );
        _lcd.print ((char)255);
    }
}