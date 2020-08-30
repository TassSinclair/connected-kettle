#ifndef connected_kettle_thermistor_h
#define connected_kettle_thermistor_h

#include "Arduino.h"

class Thermistor
{
public:
   Thermistor(
      const int thermistor_pin
      );

   float read();
   
private:
   float read_sample();
   const int _thermistor_pin;
   static const int _SAMPLE_RATE = 5;
   static const int _MAX_READ_VALUE = 4095;
   static const int _SERIES_RESISTOR_OHMS = 100000;
   static const int _THERMISTOR_NOMINAL_OMHMS = 100000;
   static const int _TEMPERATURE_NOMINAL_DEGREES = 25;
   static const int _BETA_COEFFICIENT = 3380;
   static const float _ZERO_DEGREES_KELVIN;
};

#endif
