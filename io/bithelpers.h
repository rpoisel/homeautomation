#ifndef BITHELPERS_H
#define BITHELPERS_H

#include <cstddef>
#include <cstdint>

namespace BitHelpers
{

template<typename T>
T bitflip(T pattern)
{
  return ~pattern;
}

template<typename T>
T bitflip(T& pattern, T mask)
{
  return pattern ^= mask;
}

template<typename T>
T bitflipPos(T& pattern, size_t pos)
{
  return pattern ^= (1 << pos);
}

template<typename T>
T bitmask(T pattern, T mask)
{
  return pattern & mask;
}

template<typename T>
bool bitget(T pattern, uint8_t pos)
{
  return pattern & (1 << pos);
}

template<typename T>
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

}

#endif /* BITHELPERS_H */
