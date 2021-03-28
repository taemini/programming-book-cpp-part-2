#define CATCH_CONFIG_MAIN

#include <array>
#include <map>

#include "catch.hpp"

TEST_CASE("std::multimap supports non-unique keys") {
  std::array<char, 64> far_out{
      "Far out in the uncharted backwaters of the unfashionable end..."};
  std::multimap<char, size_t> indices;
  for (size_t index{}; index < far_out.size(); index++) {
    indices.emplace(far_out[index], index);
  }
  REQUIRE(indices.count('a') == 6);

  auto [itr, end] = indices.equal_range('d');
  REQUIRE(itr->second == 23);
  itr++;
  REQUIRE(itr->second == 59);
  itr++;
  REQUIRE(itr == end);
}