#include "PLC.h"

bool PLC::RTrig::trigger(bool curState)
{
  bool retVal = (curState && !lastState);
  lastState = curState;
  return retVal;
}

PLC::MultiClick::MultiClick(Poco::Timestamp::TimeDiff window)
  : window(window), windowStart(0), cnt(0), cntLastWindow(0)
{
}

ssize_t PLC::MultiClick::call(bool value)
{
  Poco::Timestamp currentTime;

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
