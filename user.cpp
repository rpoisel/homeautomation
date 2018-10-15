#include <Arduino.h>
#include <Wire.h>

static uint8_t I2C_ADDR_OUT = 0x20;
static uint8_t I2C_ADDR_IN = 0x38;

static uint8_t states_inputs_prev = 0xff, states_outputs = 0xff;

void setup(void)
{
  Wire.begin();
}

void loop(void)
{
  uint8_t states_inputs_curr;

  Wire.requestFrom(I2C_ADDR_IN, sizeof(states_inputs_curr));
  while(Wire.available() < 1)
  {
  }
  states_inputs_curr = Wire.read();

  states_outputs ^= ((~states_inputs_prev) & states_inputs_curr);

  Wire.beginTransmission(I2C_ADDR_OUT);
  Wire.write(states_outputs);
  Wire.endTransmission();

  states_inputs_prev = states_inputs_curr;

  delay(20);
}

