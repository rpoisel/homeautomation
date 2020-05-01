#ifndef PLC_H
#define PLC_H

#include <Arduino.h>
#ifdef ARDUINO_ARCH_AVR
#include <stddef.h>
#include <stdint.h>
#else
#include <cstdint>
#endif

namespace PLC
{

class RTrig final
{
  private:
  bool lastState;

  public:
  RTrig() : RTrig(0) {}
  explicit RTrig(bool curState) : lastState(curState) {}
  ~RTrig() {}

  bool trigger(bool curState);

  private:
  RTrig(RTrig const&) = delete;
  RTrig& operator=(RTrig const&) = delete;
};

using Period = unsigned long;
using Timestamp = unsigned long;

class MultiClick final
{
  public:
  explicit MultiClick(Period const& period)
      : period(period), windowStart(0), cnt(0), cntLastWindow(0)
  {}
  ~MultiClick() {}
  size_t call(bool value);

  private:
  MultiClick(MultiClick const&) = delete;
  MultiClick& operator=(MultiClick const&) = delete;

  inline bool windowEndReached(Timestamp const& currentTime) const
  {
    return currentTime - windowStart > period;
  }

  Period period;
  Timestamp windowStart;
  size_t cnt;
  size_t cntLastWindow;
  RTrig inputTrig;
  RTrig timeTrig;
};

} // namespace PLC

#endif /* PLC_H */
