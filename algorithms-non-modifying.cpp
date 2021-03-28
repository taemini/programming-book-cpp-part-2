#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("search_n") {
  vector<string> words{"an", "orange", "owl", "owl", "owl", "today"};
  const auto result = search_n(words.cbegin(), words.cend(), 3, "owl");
  REQUIRE(result == words.cbegin() + 2);
}

TEST_CASE("search") {
  vector<string> words1{"Nine", "new", "neckties", "and", "a", "nightshirt"};
  vector<string> words2{"and", "a", "nightshirt"};
  const auto search_result_1 =
      search(words1.cbegin(), words1.cend(), words2.cbegin(), words2.cend());
  REQUIRE(*search_result_1 == "and");

  vector<string> words3{"and", "a", "nightpant"};
  const auto search_result_2 =
      search(words1.cbegin(), words1.cend(), words3.cbegin(), words3.cend());
  REQUIRE(search_result_2 == words1.cend());
}

TEST_CASE("is_permuation") {
  vector<string> words1{"moonlight", "mighty", "nice"};
  vector<string> words2{"nice", "moonlight", "mighty"};
  const auto result =
      is_permutation(words1.cbegin(), words1.cend(), words2.cbegin());
  REQUIRE(result);
}

TEST_CASE("equal") {
  vector<string> words1{"Lazy", "lion", "licks"};
  vector<string> words2{"Lazy", "lion", "kicks"};
  const auto equal_result1 =
      equal(words1.cbegin(), words1.cend(), words2.cbegin());
  REQUIRE_FALSE(equal_result1);

  words2[2] = words1[2];
  const auto equal_result2 =
      equal(words1.cbegin(), words1.cend(), words2.cbegin());
  REQUIRE(equal_result2);
}

TEST_CASE("mismatch") {
  vector<string> words1{"Kitten", "Kangaroo", "Kick"};
  vector<string> words2{"Kitten", "bandicoot", "roundhouse"};
  const auto mismatch_result1 =
      mismatch(words1.cbegin(), words1.cend(), words2.cbegin());
  REQUIRE(*mismatch_result1.first == "Kangaroo");
  REQUIRE(*mismatch_result1.second == "bandicoot");

  const auto second_letter_matches = [](const auto& word1, const auto& word2) {
    if (word1.size() < 2) return false;
    if (word2.size() < 2) return false;
    return word1[1] == word2[1];
  };
  const auto mismatch_result2 = mismatch(
      words1.cbegin(), words1.cend(), words2.cbegin(), second_letter_matches);
  REQUIRE(*mismatch_result2.first == "Kick");
  REQUIRE(*mismatch_result2.second == "roundhouse");
}

TEST_CASE("count") {
  vector<string> words{"jelly", "jar", "and", "jam"};
  const auto n_ands = count(words.cbegin(), words.cend(), "and");
  REQUIRE(n_ands == 1);

  const auto contains_a = [](const auto& word) {
    return word.find('a') != string::npos;
  };
  const auto count_if_result =
      count_if(words.cbegin(), words.cend(), contains_a);
  REQUIRE(count_if_result == 3);
}

TEST_CASE("adjacent_find") {
  vector<string> words{"Icabod", "is", "itchy"};
  const auto first_letters_match = [](const auto& word1, const auto& word2) {
    if (word1.empty() || word2.empty()) return false;
    return word1.front() == word2.front();
  };
  const auto adjacent_find_result =
      adjacent_find(words.cbegin(), words.cend(), first_letters_match);
  REQUIRE(*adjacent_find_result == words[1]);
}

TEST_CASE("find_first_of") {
  vector<string> words{"Hen", "in", "a", "hat"};
  vector<string> indefinite_articles{"a", "an"};
  const auto find_first_of_result =
      find_first_of(words.cbegin(), words.cend(), indefinite_articles.cbegin(),
                    indefinite_articles.cend());
  REQUIRE(*find_first_of_result == words[2]);
}

TEST_CASE("find_end") {
  vector<string> words1{"Goat", "girl", "googoo", "goggles"};
  vector<string> words2{"girl", "googoo"};
  const auto find_end_result1 =
      find_end(words1.cbegin(), words1.cend(), words2.cbegin(), words2.cend());
  REQUIRE(*find_end_result1 == words1[1]);

  const auto has_length = [](const auto& word, const auto& len) {
    return word.length() == len;
  };
  vector<size_t> sizes{4, 6};
  const auto find_end_result2 = find_end(
      words1.cbegin(), words1.cend(), sizes.cbegin(), sizes.cend(), has_length);
  REQUIRE(*find_end_result2 == words1[1]);
}

TEST_CASE("find find_if find_if_not") {
  vector<string> words{"fiffer", "feffer", "feff"};
  const auto find_result = find(words.cbegin(), words.cend(), "feff");
  REQUIRE(*find_result == words.back());

  const auto defends_digital_privacy = [](const auto& word) {
    return string::npos != word.find("eff");
  };
  const auto find_if_result =
      find_if(words.cbegin(), words.cend(), defends_digital_privacy);
  REQUIRE(*find_if_result == "feffer");

  const auto find_if_not_result =
      find_if_not(words.cbegin(), words.cend(), defends_digital_privacy);
  REQUIRE(*find_if_not_result == words.front());
}

TEST_CASE("for_each_n") {
  vector<string> words{"ear", "egg", "elephant"};
  size_t characters{};
  const auto count_characters = [&characters](const auto& word) {
    characters += word.size();
  };
  for_each_n(words.cbegin(), words.size(), count_characters);
  REQUIRE(14 == characters);
}

TEST_CASE("for_each") {
  vector<string> words{"David", "Donald", "Doo"};
  size_t number_of_Ds{};
  const auto count_Ds = [&number_of_Ds](const auto& word) {
    if (word.empty()) return;
    if (word[0] == 'D') ++number_of_Ds;
  };
  for_each(words.cbegin(), words.cend(), count_Ds);
  REQUIRE(3 == number_of_Ds);
}

TEST_CASE("none_of") {
  vector<string> words{"Camel", "on", "the", "ceiling"};
  const auto is_hump_day = [](const auto& word) { return word == "hump day"; };
  REQUIRE(none_of(words.cbegin(), words.cend(), is_hump_day));

  const auto is_definite_article = [](const auto& word) {
    return word == "the" || word == "ye";
  };
  REQUIRE_FALSE(none_of(words.cbegin(), words.cend(), is_definite_article));
}

TEST_CASE("any_of") {
  vector<string> words{"Barber", "baby", "bubbles"};
  const auto contains_bar = [](const auto& word) {
    return word.find("Bar") != string::npos;
  };
  REQUIRE(any_of(words.cbegin(), words.cend(), contains_bar));
  const auto is_empty = [](const auto& word) { return word.empty(); };
  REQUIRE_FALSE(any_of(words.cbegin(), words.cend(), is_empty));
}

TEST_CASE("all_of") {
  vector<string> words{"Auntie", "Anne's", "alligator"};
  const auto starts_with_a = [](const auto& word) {
    if (word.empty()) return false;
    return word[0] == 'A' || word[0] == 'a';
  };
  REQUIRE(all_of(words.cbegin(), words.cend(), starts_with_a));
  const auto has_length_six = [](const auto& word) {
    return word.length() == 6;
  };
  REQUIRE_FALSE(all_of(words.cbegin(), words.cend(), has_length_six));
}