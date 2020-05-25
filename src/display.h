#ifndef smart_kettle_display_h
#define smart_kettle_display_h

#include <LiquidCrystal.h>
#include <inttypes.h>

class Display
{
public:
   Display(LiquidCrystal lcd, 
    unsigned contrastPin,
    unsigned contrast);

   void begin();
   void clear();
   void printLoad(float load);
   void printTemperature(float temperature);
   void print(const char *line1, const char *line2);
   
private:
   LiquidCrystal _lcd;
   unsigned _contrastPin;
   unsigned _contrast;
   byte left_top[8] = {
      0b00000,
      0b00001,
      0b00010,
      0b11110,
      0b01110,
      0b00110,
      0b00010,
      0b00010
   };

   byte left_bottom[8] = {
      0b00010,
      0b00010,
      0b00010,
      0b00010,
      0b00010,
      0b00010,
      0b00110,
      0b01111
   };

   byte right_top[8] = {
      0b00000,
      0b10000,
      0b01000,
      0b01100,
      0b01110,
      0b01011,
      0b01011,
      0b01011
   };

   byte right_bottom[8] = {
      0b01011,
      0b01011,
      0b01011,
      0b01111,
      0b01110,
      0b0100,
      0b01100,
      0b11110
   };

   byte none[8] = {
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b11111,
   };


   byte some[8] = {
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b01010,
      0b11111,
      0b11111,
   };

   byte more[8] = {
      0b00000,
      0b00000,
      0b00000,
      0b01010,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
   };

   byte most[8] = {
      0b00000,
      0b01010,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
   };

   void printKettle();
   void printKettleFilling(float load);
};

#endif
