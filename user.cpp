#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>

static PCF8574 pcfIn(0x38);
static PCF8574 pcfOut(0x20);

static uint8_t states_inputs_prev = 0x00;

void setup(void)
{
  Wire.begin();
}

void loop(void)
{
  pcfOut.bitflip(BitHelpers::bitmask(BitHelpers::bitflip(states_inputs_prev), pcfIn.read()));

  states_inputs_prev = pcfIn.getCurVal();

  delay(20);
}

