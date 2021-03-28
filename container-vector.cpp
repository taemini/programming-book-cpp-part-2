#define CATCH_CONFIG_MAIN
#include <array>
#include <vector>

#include "catch.hpp"

TEST_CASE("std::vector supports default construction") {
  std::vector<const char*> vec;
  REQUIRE(vec.empty());
}

TEST_CASE("std::vector supports braced initialization") {
  std::vector<int> fib{1, 1, 2, 3, 5};
  REQUIRE(fib[4] == 5);
}

TEST_CASE("std::vector supports") {
  SECTION("braced initialization") {
    std::vector<int> five_nine{5, 9};
    REQUIRE(five_nine[0] == 5);
    REQUIRE(five_nine[1] == 9);
  }
  SECTION("fill constructor") {
    std::vector<int> five_nines(5, 9);
    REQUIRE(five_nines[0] == 9);
    REQUIRE(five_nines[4] == 9);
  }
}

TEST_CASE("std::vector supports construction from iterators") {
  std::array<int, 5> fib_arr{1, 1, 2, 3, 5};
  std::vector<int> fib_vec(fib_arr.begin(), fib_arr.end());
  REQUIRE(fib_vec[4] == 5);
  REQUIRE(fib_vec.size() == fib_arr.size());
}

TEST_CASE("std::vector assign replaces existing elements") {
  std::vector<int> message{13, 80, 110, 114, 102, 110, 101};
  REQUIRE(message.size() == 7);
  message.assign({67, 97, 101, 115, 97, 114});
  REQUIRE(message[5] == 114);
  REQUIRE(message.size() == 6);
}

TEST_CASE("std::vector insert places new elements") {
  std::vector<int> zeros(3, 0);
  auto third_element = zeros.begin() + 2;
  zeros.insert(third_element, 10);
  // do not reuse third_element iterator!
  REQUIRE(zeros[2] == 10);
  REQUIRE(zeros.size() == 4);
}

TEST_CASE("std::vector push_back places new elements") {
  std::vector<int> zeros(3, 0);  // [0, 0, 0]
  zeros.push_back(10);           // [0, 0, 0, 10]
  REQUIRE(zeros[3] == 10);
}

// emplace
TEST_CASE("std::vector emplace methods forward arguments") {
  std::vector<std::pair<int, int>> factors;
  factors.emplace_back(2, 30);
  factors.emplace_back(3, 20);
  factors.emplace_back(4, 15);
  factors.emplace(factors.begin(), 1, 60);
  REQUIRE(factors[0].first == 1);
  REQUIRE(factors[0].second == 60);
}

// storage model
TEST_CASE("std::vector exposes size management methods") {
  std::vector<std::array<uint8_t, 1024>> kb_store;
  REQUIRE(kb_store.max_size() > 0);
  REQUIRE(kb_store.empty());

  size_t elements{1024};
  kb_store.reserve(elements);
  REQUIRE(kb_store.empty());
  REQUIRE(kb_store.capacity() == elements);

  kb_store.emplace_back();
  kb_store.emplace_back();
  kb_store.emplace_back();
  REQUIRE(kb_store.size() == 3);

  kb_store.shrink_to_fit();
  REQUIRE(kb_store.capacity() == 3);

  kb_store.clear();
  REQUIRE(kb_store.empty());
  REQUIRE(kb_store.capacity() == 3);
}