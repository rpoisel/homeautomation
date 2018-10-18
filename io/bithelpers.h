#ifndef BITHELPERS_H
#define BITHELPERS_H

#include <cstdint>

namespace BitHelpers
{

template<typename T>
T bitflip(T pattern)
{
  return ~pattern;
}

template<typename T>
T bitflip(T pattern, T mask)
{
  return pattern ^ mask;
}

template<typename T>
T bitmask(T pattern, T mask)
{
  return pattern & mask;
}

}

#endif /* BITHELPERS_H */
