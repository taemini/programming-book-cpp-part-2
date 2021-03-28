#define CATCH_CONFIG_MAIN
#include <array>
#include <set>

#include "catch.hpp"

// constructing
TEST_CASE("std::set supports") {
  std::set<int> emp;
  std::set<int> fib{1, 1, 2, 3, 5};
  SECTION("default construction") { REQUIRE(emp.empty()); }
  // because set's elements are unique, size() == 4. not 5.
  SECTION("braced initialization") { REQUIRE(fib.size() == 4); }
  SECTION("copy construction") {
    auto fib_copy(fib);
    REQUIRE(fib.size() == 4);
    REQUIRE(fib_copy.size() == 4);
  }
  SECTION("move construction") {
    auto fib_moved(std::move(fib));
    REQUIRE(fib.empty());
    REQUIRE(fib_moved.size() == 4);
  }
  SECTION("range construction") {
    std::array<int, 5> fib_array{1, 1, 2, 3, 5};
    std::set<int> fib_set(fib_array.cbegin(), fib_array.cend());
    REQUIRE(fib_set.size() == 4);
  }
}

// element access
TEST_CASE("std::set allows access") {
  std::set<int> fib{1, 1, 2, 3, 5};
  SECTION("with find") {
    REQUIRE(*fib.find(3) == 3);
    REQUIRE(fib.find(100) == fib.end());
  }
  SECTION("with count") {
    REQUIRE(fib.count(3) == 1);
    REQUIRE(fib.count(100) == 0);
  }
  SECTION("with lower_bound") {
    auto itr = fib.lower_bound(3);
    REQUIRE(*itr == 3);
  }
  SECTION("with upper_bound") {
    auto itr = fib.upper_bound(3);
    REQUIRE(*itr == 5);
  }
  SECTION("with equal_range") {
    auto pair_itr = fib.equal_range(3);
    REQUIRE(*pair_itr.first == 3);
    REQUIRE(*pair_itr.second == 5);
  }
}

// adding elements
TEST_CASE("std::set allows insertion") {
  std::set<int> fib{1, 1, 2, 3, 5};
  SECTION("with insert") {
    fib.insert(8);
    REQUIRE(fib.find(8) != fib.end());
  }
  SECTION("with emplace") {
    fib.emplace(8);
    REQUIRE(fib.find(8) != fib.end());
  }
  SECTION("with emplace_hint") {
    fib.emplace_hint(fib.end(), 8);
    REQUIRE(fib.find(8) != fib.end());
  }
}

// removing elements
TEST_CASE("std::set allows removal") {
  std::set<int> fib{1, 1, 2, 3, 5};
  SECTION("with erase") {
    fib.erase(3);
    REQUIRE(fib.find(3) == fib.end());
  }
  SECTION("with clear") {
    fib.clear();
    REQUIRE(fib.empty());
  }
}