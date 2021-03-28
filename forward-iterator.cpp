#define CATCH_CONFIG_MAIN
#include <forward_list>

#include "catch.hpp"

TEST_CASE("std::forward_list's begin and end provide forward iterators") {
  const std::forward_list<int> easy_as{1, 2, 3};
  auto itr1 = easy_as.begin();
  auto itr2{itr1};
  int double_sum{};
  while (itr1 != easy_as.end()) double_sum += *(itr1++);
  while (itr2 != easy_as.end()) double_sum += *(itr2++);
  REQUIRE(double_sum == 12);
}