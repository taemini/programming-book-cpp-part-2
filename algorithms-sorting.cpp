#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("nth_element") {
  vector<int> numbers{1, 9, 2, 8, 3, 7, 4, 6, 5};
  nth_element(numbers.begin(), numbers.begin() + 5, numbers.end());
  auto less_than_6th_elem = [&elem = numbers[5]](int x) { return x < elem; };
  REQUIRE(all_of(numbers.begin(), numbers.begin() + 5, less_than_6th_elem));
  REQUIRE(numbers[5] == 6);
}

// enum class CharCategory { Ascender, Normal, Descender };
// CharCategory categorize(char x) {
//   switch (x) {
//     case 'g':
//     case 'j':
//     case 'p':
//     case 'q':
//     case 'y':
//       return CharCategory::Descender;
//     case 'b':
//     case 'd':
//     case 'f':
//     case 'h':
//     case 'k':
//     case 'l':
//     case 't':
//       return CharCategory::Ascender;
//   }
//   return CharCategory::Normal;
// }
// bool ascension_compare(char x, char y) { return categorize(x) <
// categorize(y); }

// TEST_CASE("is_sorted") {
//   string word1{"billowy"};
//   REQUIRE(is_sorted(word1.begin(), word1.end()));

//   string word2{"floppy"};
//   REQUIRE(word2.end() ==
//           is_sorted_until(word2.begin(), word2.end(), ascension_compare));
// }

// TEST_CASE("partial_sort") {
//   string word1{"nectarous"};
//   partial_sort(word1.begin(), word1.begin() + 4, word1.end());
//   REQUIRE(word1 == "acentrous");

//   string word2{"pretanning"};
//   partial_sort(word2.begin(), word2.begin() + 3, word2.end(),
//                ascension_compare);
//   REQUIRE(word2 == "terpanning");
// }

// TEST_CASE("stable_sort") {
//   string word{"outgrin"};
//   stable_sort(word.begin(), word.end(), ascension_compare);
//   REQUIRE(word == "touring");
// }

// TEST_CASE("sort") {
//   string goat_grass{"spoilage"};
//   sort(goat_grass.begin(), goat_grass.end());
//   REQUIRE(goat_grass == "aegilops");
// }