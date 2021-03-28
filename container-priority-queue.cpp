#define CATCH_CONFIG_MAIN
#include <queue>

#include "catch.hpp"

TEST_CASE("std::priority_queue supports push/pop") {
  std::priority_queue<double> prique;
  prique.push(1.0);  // 1.0
  prique.push(2.0);  // 2.0 1.0
  prique.push(1.5);  // 2.0 1.5 1.0

  REQUIRE(prique.top() == Approx(2.0));
  prique.pop();      // 1.5 1.0
  prique.push(1.0);  // 1.5 1.0 1.0
  REQUIRE(prique.top() == Approx(1.5));
  prique.pop();  // 1.0 1.0
  REQUIRE(prique.top() == Approx(1.0));
  prique.pop();  // 1.0
  REQUIRE(prique.top() == Approx(1.0));
  prique.pop();  //
  REQUIRE(prique.empty());
}