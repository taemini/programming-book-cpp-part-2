#define CATCH_CONFIG_MAIN
#include <stack>

#include "catch.hpp"

TEST_CASE("std::stack supports push/pop/top operations") {
  std::vector<int> vec{1, 3};  // 1 3
  std::stack<int, decltype(vec)> easy_as{vec};
  REQUIRE(easy_as.top() == 3);
  easy_as.pop();    // 1
  easy_as.push(2);  // 1 2
  REQUIRE(easy_as.top() == 2);
  easy_as.pop();  // 1
  REQUIRE(easy_as.top() == 1);
  easy_as.pop();
  REQUIRE(easy_as.empty());
}