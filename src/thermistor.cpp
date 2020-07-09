#include "thermistor.h"

const float Thermistor::_ZERO_DEGREES_KELVIN = -273.15;

Thermistor::Thermistor(const int thermistor_pin): _thermistor_pin(thermistor_pin)
{
};

float Thermistor::read_sample()
{
  float samples = 0;
  for (int i = 0; i < _SAMPLE_RATE; ++i)
  {
    samples += analogRead(_thermistor_pin);
    delay(10);
  }

  float resistance = _MAX_READ_VALUE / (samples / _SAMPLE_RATE) - 1;
  return _SERIES_RESISTOR_OHMS / resistance;
}

float Thermistor::read()
{  
  float resistance = read_sample();

  float value = resistance / _THERMISTOR_NOMINAL_OMHMS;
  value = log(value);
  value = (1.0 / _BETA_COEFFICIENT) * value;
  value = (1.0 / (_TEMPERATURE_NOMINAL_DEGREES - _ZERO_DEGREES_KELVIN)) + value;
  value = 1.0 / value;

  return value + _ZERO_DEGREES_KELVIN;
}