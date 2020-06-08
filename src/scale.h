#ifndef smart_kettle_scale_h
#define smart_kettle_scale_h

#include "HX711.h"

class Scale
{
public:
   Scale(
      const int dout_pin,
      const int sck_pin
      );

   void connect();
   float read();
   
private:
   HX711 _loadcell;
   static const long LOADCELL_DIVIDER = -1100000;
   // static const long LOADCELL_OFFSET = 38821; // scale tray
   static const long LOADCELL_OFFSET = -1065951; // scale tray + kettle base + kettle
   const int _dout_pin;
   const int _sck_pin;
};

#endif
