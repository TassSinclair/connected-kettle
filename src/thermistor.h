#ifndef smart_kettle_thermistor_h
#define smart_kettle_thermistor_h

class Thermistor
{
public:
   Thermistor(
      const int thermistor_pin
      );

   float read();
   
private:
   const int _thermistor_pin;
};

#endif
