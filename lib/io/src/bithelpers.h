#ifndef BITHELPERS_H
#define BITHELPERS_H

#ifdef ARDUINO_ARCH_AVR
#include <stddef.h>
#include <stdint.h>
#else
#include <cstddef>
#include <cstdint>
#endif

namespace BitHelpers
{

template <typename T>
void bitflip(T& pattern)
{
  pattern = static_cast<T>(~pattern);
}

template <typename T>
void bitflip(T& pattern, T mask)
{
  pattern ^= mask;
}

template <typename T>
void bitflipPos(T& pattern, size_t pos)
{
  pattern = static_cast<T>((pattern ^ (1 << pos)));
}

template <typename T>
void bitmask(T& pattern, T mask)
{
  return pattern &= mask;
}

template <typename T>
bool bitget(T pattern, uint8_t pos)
{
  return pattern & (1 << pos);
}

template <typename T>
void bitset(T& pattern, uint8_t pos, bool value)
{
  if (value)
  {
    pattern |= (1 << pos);
  }
  else
  {
    pattern &= ~(1 << pos);
  }
}

} // namespace BitHelpers

#endif /* BITHELPERS_H */
