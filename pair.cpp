#define CATCH_CONFIG_MAIN
#include <utility>

#include "catch.hpp"

struct Socialite {
  const char* birthname;
};
struct Valet {
  const char* surname;
};
Socialite bertie{"Willberforce"};
Valet reginald{"Jeeves"};

TEST_CASE("std::pair permits access to members") {
  // defaulted copy constructor
  std::pair<Socialite, Valet> inimitable_duo{bertie, reginald};
  REQUIRE(inimitable_duo.first.birthname == bertie.birthname);
  REQUIRE(inimitable_duo.second.surname == reginald.surname);
}

TEST_CASE("std::pair works with structured binding") {
  std::pair<Socialite, Valet> inimitable_duo{bertie, reginald};
  auto& [idle_rich, butler] = inimitable_duo;  // reference
  REQUIRE(idle_rich.birthname == bertie.birthname);
  REQUIRE(butler.surname == reginald.surname);
}