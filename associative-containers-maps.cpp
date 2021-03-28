#define CATCH_CONFIG_MAIN
#include <map>

#include "catch.hpp"

auto colour_of_magic = "Colour of magic";
auto the_light_fantastic = "The Light Fantastic";
auto equal_rites = "Equal Rites";
auto mort = "Mort";

// constructing
TEST_CASE("std::map supports") {
  SECTION("default construction") {
    std::map<const char*, int> emp;
    REQUIRE(emp.empty());
  }
  SECTION("braced initialization") {
    // nested initialization with nested initializer lists
    std::map<const char*, int> pub_year{{colour_of_magic, 1983},
                                        {the_light_fantastic, 1986},
                                        {equal_rites, 1987},
                                        {mort, 1987}};
    REQUIRE(pub_year.size() == 4);
  }
}

// element access
TEST_CASE("std::map is an associative array with") {
  std::map<const char*, int> pub_year{
      {colour_of_magic, 1983},
      {the_light_fantastic, 1986},
  };
  SECTION("operator[]") {
    REQUIRE(pub_year[colour_of_magic] == 1983);

    pub_year[equal_rites] = 1987;
    REQUIRE(pub_year[equal_rites] == 1987);

    REQUIRE(pub_year[mort] == 0);
  }
  SECTION("an at method") {
    REQUIRE(pub_year.at(colour_of_magic) == 1983);
    REQUIRE_THROWS_AS(pub_year.at(equal_rites), std::out_of_range);
  }
}

// adding elements
TEST_CASE("std::map supports insert") {
  std::map<const char*, int> pub_year;
  pub_year.insert({colour_of_magic, 1983});
  // pub_year.emplace(colour_of_magic, 1983);
  REQUIRE(pub_year.size() == 1);

  std::pair<const char*, int> tlfp{the_light_fantastic, 1986};
  pub_year.insert(tlfp);  // copy occurred
  REQUIRE(pub_year.size() == 2);

  // used braced initializer
  auto [itr, is_new] = pub_year.insert({the_light_fantastic, 9999});
  // auto [itr, is_new] = pub_year.insert(std::pair<const char*,
  // int>{colour_of_magic, 1983}); 과 같다

  REQUIRE(itr->first == the_light_fantastic);
  REQUIRE(itr->second == 1986);
  REQUIRE_FALSE(is_new);
  REQUIRE(pub_year.size() == 2);
}

// insert or assign
TEST_CASE("std::map supports insert_or_assign") {
  std::map<const char*, int> pub_year{{the_light_fantastic, 9999}};
  auto [itr, is_new] = pub_year.insert_or_assign(the_light_fantastic, 1986);
  REQUIRE(itr->second == 1986);
  REQUIRE_FALSE(is_new);
}

TEST_CASE("We can remove std::map elements using") {
  std::map<const char*, int> pub_year{{colour_of_magic, 1983}, {mort, 1987}};
  SECTION("erase") {
    pub_year.erase(mort);
    REQUIRE(pub_year.find(mort) == pub_year.end());
  }
  SECTION("clear") {
    pub_year.clear();
    REQUIRE(pub_year.empty());
  }
}