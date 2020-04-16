#include "PCF8574.h"
#include "bithelpers.h"
#include <Wire.h>

uint8_t PCF8574::read()
{
  Wire.requestFrom(address, static_cast<uint8_t>(1));
  while (Wire.available() < 1)
  {
  }
  curVal = BitHelpers::bitflip(static_cast<uint8_t>(Wire.read()));
  return curVal;
}

void PCF8574::write(uint8_t states)
{
  Wire.beginTransmission(address);
  Wire.write(BitHelpers::bitflip(states));
  Wire.endTransmission();
  curVal = states;
}
