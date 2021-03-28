#define CATCH_CONFIG_MAIN
#include <iterator>
#include <vector>

#include "catch.hpp"

TEST_CASE("distance returns the number of elements between iterators") {
  std::vector<unsigned char> mission{0x9e, 0xc4, 0xc1, 0x29, 0x49, 0xa4,
                                     0xf3, 0x14, 0x74, 0xf2, 0x99, 0x05,
                                     0x8c, 0xe2, 0xb2, 0x2a};
  auto eighth = std::next(mission.begin(), 8);
  auto fifth = std::prev(eighth, 3);
  REQUIRE(std::distance(fifth, eighth) == 3);
}