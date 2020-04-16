#include "PLC.h"

bool PLC::RTrig::trigger(bool curState)
{
  bool retVal = (curState && !lastState);
  lastState = curState;
  return retVal;
}

size_t PLC::MultiClick::call(bool value)
{
#ifdef ARDUINO_ARCH_AVR
  Timestamp currentTime = millis();
#else
  Poco::Timestamp currentTime;
#endif

  bool retVal = timeTrig.trigger(windowEndReached(currentTime));

  if (retVal)
  {
    cntLastWindow = cnt;
  }

  if (!inputTrig.trigger(value))
  {
    return retVal ? cntLastWindow : -1;
  }

  if (windowEndReached(currentTime))
  {
    windowStart = currentTime;
    cnt = 1;
  }
  else
  {
    cnt++;
  }
  return retVal ? cntLastWindow : -1;
}