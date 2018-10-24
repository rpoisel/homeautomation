#ifndef PLC_H
#define PLC_H

#include <Poco/Timestamp.h>
#include <cstdint>

namespace PLC
{

class RTrig
{
  private:
    bool lastState;

  public:
    RTrig() : RTrig(0) {}
    RTrig(bool curState) : lastState(curState) {}
    virtual ~RTrig() {}

    virtual bool trigger(bool curState);
};

class MultiClick
{
  private:
    Poco::Timestamp::TimeDiff const window;
    Poco::Timestamp windowStart;
    size_t cnt;
    ssize_t cntLastWindow;
    RTrig inputTrig;
    RTrig timeTrig;

    inline bool windowEndReached(Poco::Timestamp& currentTime) const { return currentTime - windowStart > window; }

  public:
    MultiClick(Poco::Timestamp::TimeDiff window);
    virtual ~MultiClick() {}

    virtual ssize_t call(bool value);
};

}

#endif /* PLC_H */
