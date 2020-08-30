#ifndef connected_kettle_display_h
#define connected_kettle_display_h

#include "LiquidCrystal.h"
#include "inttypes.h"
#include "analogWrite.h"
#include "Wire.h"

class Display
{
public:
   Display(LiquidCrystal lcd, 
    unsigned contrast_pin,
    unsigned contrast);

   void connect();
   void clear();
   void set_backlight(bool on);
   void print_load(float load);
   void print_temperature(float temperature);
   void print(const char *line_1, const char *line_2);
   
private:
   LiquidCrystal _lcd;
   unsigned _contrast_pin;
   unsigned _contrast;

   static byte _KETTLE_LEFT_TOP[];
   static byte _KETTLE_LEFT_BOTTOM[];
   static byte _KETTLE_RIGHT_TOP[];
   static byte _KETTLE_RIGHT_BOTTOM[];

   static byte _KETTLE_FILL_NONE[];
   static byte _KETTLE_FILL_SOME[];
   static byte _KETTLE_FILL_MORE[];
   static byte _KETTLE_FILL_MOST[];

   void print_kettle();
   void print_kettle_filling(float load);
};

#endif
