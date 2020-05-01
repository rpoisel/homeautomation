#include <Arduino.h>
#include <PCF8574.h>
#include <PLC.h>
#include <Wire.h>

using namespace BitHelpers;

static unsigned long lastDebug;

void setup(void)
{
  Wire.begin();
  Wire.setClock(32000);
  Serial.begin(19200);

  Serial.println("setup() done.");
  lastDebug = millis();
}

void loop(void)
{
  static PCF8574 pcfIn(0x38);
  static PCF8574 pcfOut(0x20);
  static uint8_t const simpleInputs[] = {0, 1, 2, 3, 4, 6, 7};
  static PLC::RTrig triggerInputs[sizeof(simpleInputs) / sizeof(simpleInputs[0])];
  static PLC::MultiClick multiClickBit5(300);

  uint8_t outputStates = pcfOut.getCurVal();
  uint8_t const inputStates = pcfIn.read();

  auto curDebug = millis();
  if (curDebug - lastDebug > 500)
  {
    Serial.print("Alive. InputStates: ");
    Serial.print(inputStates, HEX);
    Serial.print(", OutputStates: ");
    Serial.println(outputStates, HEX);

    lastDebug = curDebug;
  }

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

  pcfOut.write(outputStates);

  delay(20);
}
