#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>
#include <PLC.h>

#include <vector>

using namespace BitHelpers;

void setup(void)
{
  Wire.begin();
}

void loop(void)
{
  static PCF8574 pcfIn(0x38);
  static PCF8574 pcfOut(0x20);

  uint8_t outputStates = pcfOut.getCurVal();
  uint8_t const inputStates = pcfIn.read();

  static std::vector<size_t> const simpleInputs = {0, 1, 2, 3, 4, 6, 7};
  static std::vector<PLC::RTrig> triggerInputs(simpleInputs.size());
  static PLC::MultiClick multiClickBit5(1000000);

  for (auto idx = 0; idx < simpleInputs.size(); idx++)
  {
    if (triggerInputs[idx].trigger(bitget(inputStates, simpleInputs[idx])))
    {
      bitflipPos(outputStates, simpleInputs[idx]);
    }
  }

  switch(multiClickBit5.call(bitget(inputStates, 5)))
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

  pcfOut.write(outputStates);

  delay(20);
}

