#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void setup(void);
void loop(void);
void teardown(void);

void delay(unsigned long ms);
unsigned long millis();

#ifdef __cplusplus
}
#endif /* __cplusplus */

enum NumberFormat : uint8_t
{
  DEC,
  HEX,
  OCT
};

using NumberFormat::DEC;
using NumberFormat::HEX;
using NumberFormat::OCT;

class SerialClass
{
  public:
  void begin(uint32_t baud) {}
  bool operator!() const { return false; }
  void println(char const* msg) { std::cout << msg << std::endl; }
  void print(char const* msg) { std::cout << msg << std::flush; }
  void println(size_t num, NumberFormat fmt) { std::cout << num << std::endl; }
  void print(size_t num, NumberFormat fmt) { std::cout << num << std::flush; }
  void println(uint32_t num) { std::cout << num << std::endl; }
};

extern SerialClass Serial;

#endif /* ARDUINO_H */
