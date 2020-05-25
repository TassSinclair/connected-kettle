#ifndef smart_kettle_scale_h
#define smart_kettle_scale_h

#include "HX711.h"

class Scale
{
public:
   Scale(
      const int DOUT_PIN,
      const int SCK_PIN
      );

   void begin();
   float read();
   
private:
   HX711 _loadcell;
   const long LOADCELL_DIVIDER = -1100000;
   const long LOADCELL_OFFSET = 38821;
   const int _dout_pin;
   const int _sck_pin;
};

#endif
