#define CATCH_CONFIG_MAIN

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>

#include "catch.hpp"

TEST_CASE("boost::algorithm") {
  using namespace boost::algorithm;
  using namespace std::literals::string_literals;
  std::string word("cymotrichous");
  SECTION("starts_with tests a string's begining") {
    REQUIRE(starts_with(word, "cymo"s));
  }
  SECTION("istarts_with is case insensitive") {
    REQUIRE(istarts_with(word, "cYmO"s));
  }
}

TEST_CASE("boost::algorithm::all evaluates a predicate for all elements") {
  using namespace boost::algorithm;
  std::string word("juju");
  REQUIRE(all(word, [](auto c) { return c == 'j' || c == 'u'; }));
}

TEST_CASE("boost::algorithm::is_alnum") {
  using namespace boost::algorithm;
  const auto classifier = is_alnum();
  SECTION("evaluates alphanumeric characters") {
    REQUIRE(classifier('a'));
    REQUIRE_FALSE(classifier('$'));
  }
  SECTION("works with all") {
    REQUIRE(all("nostartch", classifier));
    REQUIRE_FALSE(all("@nostartch", classifier));
  }
}

TEST_CASE("boost::algorithm::nth_finder finds the nth occurrence") {
  const auto finder = boost::algorithm::nth_finder("na", 1);
  std::string name("Carl Brutananadilewski");
  const auto result = finder(name.begin(), name.end());
  REQUIRE(result.begin() == name.begin() + 12);  // Carl Brutana(n)adilewski
  REQUIRE(result.end() == name.begin() + 14);    // Carl Brutanana(d)ilewski
}

TEST_CASE("boost::algorithm::to_upper") {
  std::string powers("difficulty controlling the volume of my voice");
  SECTION("upper-case a string") {
    boost::algorithm::to_upper(powers);
    REQUIRE(powers == "DIFFICULTY CONTROLLING THE VOLUME OF MY VOICE");
  }
  SECTION("_copy leaves the original unmodified") {
    auto result = boost::algorithm::to_upper_copy(powers);
    REQUIRE(powers == "difficulty controlling the volume of my voice");
    REQUIRE(result == "DIFFICULTY CONTROLLING THE VOLUME OF MY VOICE");
  }
}

TEST_CASE("boost::algorithm::replace_first") {
  using namespace boost::algorithm;
  std::string publisher("No Starch Press");
  SECTION("replaces the first occurrence of a string") {
    replace_first(publisher, "No", "Medium");
    REQUIRE(publisher == "Medium Starch Press");
  }
  SECTION("has a case-insensitive variant") {
    auto result = ireplace_first_copy(publisher, "NO", "MEDIUM");
    REQUIRE(publisher == "No Starch Press");
    REQUIRE(result == "MEDIUM Starch Press");
  }
}

TEST_CASE("boost::algorithm::split splits a range based on a predicate") {
  using namespace boost::algorithm;
  std::string publisher("No Starch Press");
  std::vector<std::string> tokens;
  split(tokens, publisher, is_space());
  REQUIRE(tokens[0] == "No");
  REQUIRE(tokens[1] == "Starch");
  REQUIRE(tokens[2] == "Press");
}

TEST_CASE("boost::algorithm::join staples tokens together") {
  std::vector<std::string> tokens{"We invited the strippers", "JFK",
                                  "and Stalin."};
  auto result = boost::algorithm::join(tokens, ", ");
  REQUIRE(result == "We invited the strippers, JFK, and Stalin.");
}

TEST_CASE("boost::algorithm::find_head computes the head") {
  std::string word("blandishment");
  const auto result = boost::algorithm::find_head(word, 5);
  REQUIRE(result.begin() == word.begin());    // (b)landishment
  REQUIRE(result.end() == word.begin() + 5);  // bland(i)shment
}

TEST_CASE("boost::tokenizer splits token-delimited strings") {
  std::string palindrome("A man, a plan, a canal, Panama!");
  boost::char_separator<char> comma{","};
  boost::tokenizer<boost::char_separator<char>> tokens{palindrome, comma};
  auto itr = tokens.begin();
  REQUIRE(*itr == "A man");
  itr++;
  REQUIRE(*itr == " a plan");
  itr++;
  REQUIRE(*itr == " a canal");
  itr++;
  REQUIRE(*itr == " Panama!");
}