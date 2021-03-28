#define CATCH_CONFIG_MAIN
#include <iterator>
#include <vector>

#include "catch.hpp"

struct Movable {
  Movable(int id) : id{id} {}
  Movable(Movable&& m) {
    id = m.id;
    m.id = -1;
  }
  int id;
};

TEST_CASE("move iterators convert accesses into move operations") {
  std::vector<Movable> donor;
  donor.emplace_back(1);
  donor.emplace_back(2);
  donor.emplace_back(3);
  // range constructor of std::vector
  std::vector<Movable> recipient{std::make_move_iterator(donor.begin()),
                                 std::make_move_iterator(donor.end())};
  REQUIRE(donor[0].id == -1);  // becomes "moved-from state"
  REQUIRE(donor[1].id == -1);
  REQUIRE(donor[2].id == -1);
  REQUIRE(recipient[0].id == 1);
  REQUIRE(recipient[1].id == 2);
  REQUIRE(recipient[2].id == 3);
}