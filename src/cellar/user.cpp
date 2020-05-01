#include <Arduino.h>
#include <PCF8574.h>
#include <PLC.h>
#include <Wire.h>

using namespace BitHelpers;

static PCF8574 pcfOut(0x20);

void setup(void)
{
  Wire.begin();
  Wire.setClock(32000);

  pcfOut.write(0);
}

void loop(void)
{
  static PCF8574 pcfIn(0x38);
  static uint8_t const simpleInputs[] = {0, 1, 2, 3, 4, 6, 7};
  static PLC::RTrig triggerInputs[sizeof(simpleInputs) / sizeof(simpleInputs[0])];
  static PLC::MultiClick multiClickBit5(300);

  uint8_t outputStates = pcfOut.getCurVal();
  uint8_t const inputStates = pcfIn.read();

  for (size_t idx = 0; idx < (sizeof(simpleInputs) / sizeof(simpleInputs[0])); idx++)
  {
    if (triggerInputs[idx].trigger(bitget(inputStates, simpleInputs[idx])))
    {
      bitflipPos(outputStates, simpleInputs[idx]);
    }
  }

  switch (multiClickBit5.call(bitget(inputStates, 5)))
  {
  case 1 /* single click */:
    bitflipPos(outputStates, 5);
    break;
  case 2 /* double click */:
    bitflipPos(outputStates, 2);
    break;
  default:
    break;
  }

  if (outputStates != pcfOut.getCurVal())
  {
    pcfOut.write(outputStates);
  }

  delay(20);
}
