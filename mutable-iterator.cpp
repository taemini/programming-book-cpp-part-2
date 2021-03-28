#define CATCH_CONFIG_MAIN
#include <deque>

#include "catch.hpp"

TEST_CASE("Mutable random-access iterators support writing.") {
  std::deque<int> easy_as{1, 0, 3};
  auto itr = easy_as.begin();
  itr[1] = 2;
  itr++;
  REQUIRE(*itr == 2);
}