#define CATCH_CONFIG_MAIN
#include <iterator>

#include "catch.hpp"

TEST_CASE("advance modifies input iterators") {
  std::vector<unsigned char> mission{0x9e, 0xc4, 0xc1, 0x29, 0x49, 0xa4,
                                     0xf3, 0x14, 0x74, 0xf2, 0x99, 0x05,
                                     0x8c, 0xe2, 0xb2, 0x2a};
  auto itr = mission.begin();
  std::advance(itr, 4);
  REQUIRE(*itr == 0x49);
  std::advance(itr, 4);
  REQUIRE(*itr == 0x74);
  std::advance(itr, -8);
  REQUIRE(*itr == 0x9e);
}