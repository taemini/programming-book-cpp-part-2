#define CATCH_CONFIG_MAIN
#include <list>
#include <vector>

#include "catch.hpp"

TEST_CASE("reverse iterators can initialize containers") {
  std::list<int> original{3, 2, 1};
  std::vector<int> easy_as{original.crbegin(), original.crend()};
  REQUIRE(easy_as[0] == 1);
  REQUIRE(easy_as[1] == 2);
  REQUIRE(easy_as[2] == 3);
}

TEST_CASE("make_reverse_iterator converts a normal iterator") {
  std::list<int> original{3, 2, 1};
  auto begin = std::make_reverse_iterator(original.cend());
  auto end = std::make_reverse_iterator(original.cbegin());
  std::vector<int> easy_as{begin, end};
  REQUIRE(easy_as[0] == 1);
  REQUIRE(easy_as[1] == 2);
  REQUIRE(easy_as[2] == 3);
}