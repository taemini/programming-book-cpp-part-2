#define CATCH_CONFIG_MAIN
#include <deque>
#include <iterator>

#include "catch.hpp"

TEST_CASE("Insert iterators convert writes into container insertions.") {
  std::deque<int> dq;
  auto back_instr = std::back_inserter(dq);
  *back_instr = 2;  // 2
  ++back_instr;
  *back_instr = 4;  // 2 4
  ++back_instr;

  auto front_instr = std::front_inserter(dq);
  *front_instr = 1;  // 1 2 4
  ++front_instr;

  auto instr = std::inserter(dq, dq.begin() + 2);
  *instr = 3;  // 1 2 3 4
  instr++;

  REQUIRE(dq[0] == 1);
  REQUIRE(dq[1] == 2);
  REQUIRE(dq[2] == 3);
  REQUIRE(dq[3] == 4);
}
