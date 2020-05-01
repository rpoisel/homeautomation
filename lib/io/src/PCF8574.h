#ifndef PCR8574_H
#define PCR8574_H

#include "bithelpers.h"

class PCF8574 final
{
  private:
  uint8_t const address;
  uint8_t curVal;

  void internalWrite(uint8_t states);

  public:
  explicit PCF8574(uint8_t address) : address(address), curVal(0) {}
  ~PCF8574() {}

  inline void begin(uint8_t states) { internalWrite(states); }
  uint8_t read(void);
  void write(uint8_t states);
  inline uint8_t getCurVal(void) const { return curVal; }
};

#endif /* PCF8574_H */
