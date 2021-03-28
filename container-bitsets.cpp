#define CATCH_CONFIG_MAIN
#include <bitset>

#include "catch.hpp"

TEST_CASE("std::bitset supports integer initialization") {
  std::bitset<4> bs(0b1010);
  REQUIRE_FALSE(bs[0]);
  REQUIRE(bs[1]);
  REQUIRE_FALSE(bs[2]);
  REQUIRE(bs[3]);
}

TEST_CASE("std::bitset supports string initialization") {
  std::bitset<4> bs1(0b0110);
  std::bitset<4> bs2("0110");
  REQUIRE(bs1 == bs2);
}