#include "scale.h"

Scale::Scale(
    const int dout_pin,
    const int sck_pin
) : _dout_pin(dout_pin), _sck_pin(sck_pin) {

}

void Scale::begin()
{
    _loadcell.begin(_dout_pin, _sck_pin);
    _loadcell.set_scale(LOADCELL_DIVIDER); //Adjust to this calibration factor
    _loadcell.set_offset(LOADCELL_OFFSET);
    _loadcell.tare();
}

inline float max(float a, float b) { return a > b ? a : b; }

float Scale::read()
{
    return max(_loadcell.get_units(10), 0);
}