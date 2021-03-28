#define CATCH_CONFIG_MAIN
#include <array>
#include <deque>

#include "catch.hpp"

TEST_CASE("std::deque supports front insertion") {
  std::deque<char> deckard;
  deckard.push_front('a');  // a
  deckard.push_back('i');   // ai
  deckard.push_front('c');  // cai
  deckard.push_back('n');   // cain
  REQUIRE(deckard[0] == 'c');
  REQUIRE(deckard[1] == 'a');
  REQUIRE(deckard[2] == 'i');
  REQUIRE(deckard[3] == 'n');
}