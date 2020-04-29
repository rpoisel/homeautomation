#include "PCF8574.h"
#include "bithelpers.h"
#include <Wire.h>

uint8_t PCF8574::read()
{
  Wire.requestFrom(address, static_cast<uint8_t>(1));
  while (Wire.available() < 1)
  {
  }
  curVal = static_cast<uint8_t>(Wire.read());
  BitHelpers::bitflip(curVal);
  return curVal;
}

void PCF8574::write(uint8_t states)
{
  Wire.beginTransmission(address);
  BitHelpers::bitflip(states);
  Wire.write(states);
  Wire.endTransmission();
  curVal = states;
}
