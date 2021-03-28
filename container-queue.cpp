#define CATCH_CONFIG_MAIN
#include <queue>

#include "catch.hpp"

TEST_CASE("std::queue supports push/pop/front/back") {
  std::deque<int> deq{1, 2};
  std::queue<int> easy_as(deq);  // 1 2

  REQUIRE(easy_as.front() == 1);
  REQUIRE(easy_as.back() == 2);
  easy_as.pop();    // 2
  easy_as.push(3);  // 2 3
  REQUIRE(easy_as.front() == 2);
  REQUIRE(easy_as.back() == 3);
  easy_as.pop();  // 3
  REQUIRE(easy_as.front() == 3);
  easy_as.pop();
  REQUIRE(easy_as.empty());
}