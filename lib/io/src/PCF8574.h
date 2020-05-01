#ifndef PCR8574_H
#define PCR8574_H

#include "bithelpers.h"

class PCF8574
{
  private:
  uint8_t const address;
  uint8_t curVal;

  public:
  PCF8574(uint8_t address) : address(address), curVal(0) {}
  virtual ~PCF8574() {}

  virtual uint8_t read(void);
  virtual void write(uint8_t states);
  inline virtual uint8_t getCurVal(void) const { return curVal; }
};

#endif /* PCF8574_H */
