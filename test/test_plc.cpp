#include <PLC.h>

#include <catch2/catch.hpp>

TEST_CASE("Multiclick default use-case", "[single-file]")
{
  setMillis(0);
  PLC::MultiClick multiclick(300);
  REQUIRE(multiclick.call(true) == -1);
  REQUIRE(multiclick.call(false) == -1);
  setMillis(200);
  REQUIRE(multiclick.call(true) == -1);
  setMillis(300);
  REQUIRE(multiclick.call(false) == -1);
  setMillis(301);
  REQUIRE(multiclick.call(false) == 2);
}

TEST_CASE("Multiclick all false", "[single-file]")
{
  setMillis(0);
  PLC::MultiClick multiclick(300);
  REQUIRE(multiclick.call(false) == -1);
  REQUIRE(multiclick.call(false) == -1);
  REQUIRE(multiclick.call(false) == -1);
  setMillis(100);
  REQUIRE(multiclick.call(false) == -1);
  REQUIRE(multiclick.call(false) == -1);
  REQUIRE(multiclick.call(false) == -1);
  setMillis(200);
  REQUIRE(multiclick.call(false) == -1);
  setMillis(300);
  REQUIRE(multiclick.call(false) == -1);
  setMillis(301);
  REQUIRE(multiclick.call(false) == 0);
}

TEST_CASE("Multiclick all true", "[single-file]")
{
  setMillis(0);
  PLC::MultiClick multiclick(300);
  REQUIRE(multiclick.call(true) == -1);
  REQUIRE(multiclick.call(true) == -1);
  REQUIRE(multiclick.call(true) == -1);
  setMillis(100);
  REQUIRE(multiclick.call(true) == -1);
  REQUIRE(multiclick.call(true) == -1);
  REQUIRE(multiclick.call(true) == -1);
  setMillis(200);
  REQUIRE(multiclick.call(true) == -1);
  setMillis(300);
  REQUIRE(multiclick.call(true) == -1);
  setMillis(301);
  REQUIRE(multiclick.call(true) == 1);
}
