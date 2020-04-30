#include <bithelpers.h>

#include <catch2/catch.hpp>

TEST_CASE("Bit Flipping (8 bits)", "[single-file]")
{
  uint8_t bits = 0x00;
  BitHelpers::bitflip(bits);
  REQUIRE(bits == 0xff);
  BitHelpers::bitflip(bits);
  REQUIRE(bits == 0x00);
}

TEST_CASE("Bit Flipping (16 bits)", "[single-file]")
{
  uint16_t bits = 0x5555;
  BitHelpers::bitflip(bits);
  REQUIRE(bits == 0xaaaa);
  BitHelpers::bitflip(bits);
  REQUIRE(bits == 0x5555);
}

TEST_CASE("Bit Flipping with mask (8 bits)", "[single-file]")
{
  uint8_t bits = 0x00;
  uint8_t const mask1 = 0x0f;
  uint8_t const mask2 = 0xf0;
  BitHelpers::bitflip(bits, mask1);
  REQUIRE(bits == 0x0f);
  BitHelpers::bitflip(bits, mask2);
  REQUIRE(bits == 0xff);
}

TEST_CASE("Bit Flipping at position (8 bits)", "[single-file]")
{
  uint16_t bits = 0x55;
  BitHelpers::bitflipPos(bits, 0);
  REQUIRE(bits == 0x54);
  BitHelpers::bitflipPos(bits, 7);
  REQUIRE(bits == 0xd4);
}

TEST_CASE("Bit Masking (8 bits)", "[single-file]")
{
  uint8_t bits = 0x55;
  uint8_t const mask1 = 0xf0;
  uint8_t const mask2 = 0x0f;
  BitHelpers::bitmask(bits, mask1);
  REQUIRE(bits == 0x50);
  BitHelpers::bitmask(bits, mask2);
  REQUIRE(bits == 0x00);
}

TEST_CASE("Bit Getting (8 bits)", "[single-file]")
{
  uint8_t bits = 0x55;
  REQUIRE(BitHelpers::bitget(bits, 0) == true);
  REQUIRE(BitHelpers::bitget(bits, 1) == false);
  REQUIRE(BitHelpers::bitget(bits, 2) == true);
  REQUIRE(BitHelpers::bitget(bits, 3) == false);
  REQUIRE(BitHelpers::bitget(bits, 4) == true);
  REQUIRE(BitHelpers::bitget(bits, 5) == false);
  REQUIRE(BitHelpers::bitget(bits, 6) == true);
  REQUIRE(BitHelpers::bitget(bits, 7) == false);
}

TEST_CASE("Bit Setting (8 bits)", "[single-file]")
{
  uint8_t bits = 0x55;
  BitHelpers::bitset(bits, 0, false);
  REQUIRE(bits == 0x54);
  BitHelpers::bitset(bits, 1, true);
  REQUIRE(bits == 0x56);
  BitHelpers::bitset(bits, 2, false);
  REQUIRE(bits == 0x52);
  BitHelpers::bitset(bits, 3, true);
  REQUIRE(bits == 0x5a);
  BitHelpers::bitset(bits, 4, false);
  REQUIRE(bits == 0x4a);
  BitHelpers::bitset(bits, 5, true);
  REQUIRE(bits == 0x6a);
  BitHelpers::bitset(bits, 6, false);
  REQUIRE(bits == 0x2a);
  BitHelpers::bitset(bits, 7, true);
  REQUIRE(bits == 0xaa);
}
