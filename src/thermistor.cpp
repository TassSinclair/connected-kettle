#include "thermistor.h"

#include <Arduino.h>

Thermistor::Thermistor(const int thermistor_pin): _thermistor_pin(thermistor_pin)
{
};


inline float max(float a, float b) { return a > b ? a : b; }

float Thermistor::read()
{
  #define SAMPLE_RATE 5
  
  float samples = 0;
  for (int i = 0; i < SAMPLE_RATE; ++i)
  {
    samples += analogRead(_thermistor_pin);
    delay(10);
  }

  #define SERIES_RESISTOR_OHMS 100000
  float resistance = 4095 / (samples / SAMPLE_RATE) - 1;
  resistance = SERIES_RESISTOR_OHMS / resistance;

  #define THERMISTOR_NOMINAL_OMHMS 100000
  #define TEMPERATURE_NOMINAL_DEGREES 25
  #define BETA_COEFFICIENT 3380
  float steinhart = resistance / THERMISTOR_NOMINAL_OMHMS;
  steinhart = log(steinhart);
  steinhart = (1.0 / BETA_COEFFICIENT) * steinhart;
  steinhart = (1.0 / (TEMPERATURE_NOMINAL_DEGREES + 273.15)) + steinhart;
  steinhart = 1.0/steinhart;

  float celsius = steinhart - 273.15;
  return max(celsius, 0);
}