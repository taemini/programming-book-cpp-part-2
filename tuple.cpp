#define CATCH_CONFIG_MAIN
#include <tuple>

#include "catch.hpp"

struct Socialite {
  const char* birthname;
};
struct Valet {
  const char* surname;
};
struct Acquaintance {
  const char* nickname;
};
Socialite bertie{"Willberforce"};
Valet reginald{"Jeeves"};
Acquaintance hildebrand{"Tuppy"};

TEST_CASE("std::tuple permits access to members with std::get") {
  using Trio = std::tuple<Socialite, Valet, Acquaintance>;
  Trio truculent_trio{bertie, reginald, hildebrand};
  auto& bertie_ref = std::get<0>(truculent_trio);
  REQUIRE(bertie_ref.birthname == bertie.birthname);

  auto& tuppy_ref = std::get<Acquaintance>(truculent_trio);
  REQUIRE(tuppy_ref.nickname == hildebrand.nickname);
}