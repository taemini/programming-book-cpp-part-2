#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("reverse") {
  string stinky = "diaper";
  reverse(stinky.begin(), stinky.end());
  REQUIRE(stinky == "repaid");
}

TEST_CASE("unique") {
  string without_walls = "Wallless";
  const auto new_end = unique(without_walls.begin(), without_walls.end());
  without_walls.erase(new_end, without_walls.end());
  REQUIRE(without_walls == "Wales");
}

TEST_CASE("remove") {
  auto is_vowel = [](char x) {
    const static string vowels{"aeiouAEIOU"};
    return vowels.find(x) != string::npos;
  };
  string pilgrim =
      "Among the things Billy Pilgrim could not change "
      "were the past, the present, and the future.";
  const auto new_end = remove_if(pilgrim.begin(), pilgrim.end(), is_vowel);
  REQUIRE(pilgrim ==
          "mng th thngs Blly Plgrm cld nt chng wr th pst, "
          "th prsnt, nd th ftr.present, and the future.");

  pilgrim.erase(new_end, pilgrim.end());
  REQUIRE(pilgrim ==
          "mng th thngs Blly Plgrm cld nt chng wr th "
          "pst, th prsnt, nd th ftr.");
}

TEST_CASE("generate") {
  auto i{1};
  auto pow_of_2 = [&i]() {
    const auto tmp = i;
    i *= 2;
    return tmp;
  };
  vector<int> series1(6);
  generate(series1.begin(), series1.end(), pow_of_2);
  REQUIRE(series1 == vector<int>{1, 2, 4, 8, 16, 32});

  vector<int> series2;
  generate_n(back_inserter(series2), 6, pow_of_2);
  REQUIRE(series2 == vector<int>{64, 128, 256, 512, 1024, 2048});
}

TEST_CASE("fill") {
  vector<string> answer1(6);
  fill(answer1.begin(), answer1.end(), "police");
  REQUIRE(answer1 == vector<string>{"police", "police", "police", "police",
                                    "police", "police"});

  vector<string> answer2;
  fill_n(back_inserter(answer2), 6, "police");
  REQUIRE(answer2 == vector<string>{"police", "police", "police", "police",
                                    "police", "police"});
}

#include <string_view>
TEST_CASE("replace") {
  using namespace std::literals;
  vector<string> words1{"There", "is", "no", "try"};
  replace(words1.begin(), words1.end(), "try"sv, "spoon"sv);
  REQUIRE(words1 == vector<string>{"There", "is", "no", "spoon"});

  const vector<string> words2{"There", "is", "no", "spoon"};
  vector<string> words3{"There", "is", "no", "spoon"};
  auto has_two_os = [](const auto& x) {
    return count(x.begin(), x.end(), 'o') == 2;
  };
  replace_copy_if(words2.begin(), words2.end(), words3.begin(), has_two_os,
                  "try"sv);
  REQUIRE(words3 == vector<string>{"There", "is", "no", "try"});
}

#include <boost/algorithm/string/case_conv.hpp>
TEST_CASE("transform") {
  vector<string> words1{"farewell", "hello", "farewell", "hello"};
  vector<string> result1;
  auto upper = [](string x) {
    boost::algorithm::to_upper(x);
    return x;
  };
  transform(words1.begin(), words1.end(), back_inserter(result1), upper);
  REQUIRE(result1 == vector<string>{"FAREWELL", "HELLO", "FAREWELL", "HELLO"});

  vector<string> words2{"light", "human", "bro", "quantum"};
  vector<string> words3{"radar", "robot", "pony", "bit"};
  vector<string> result2;
  auto portmantize = [](const auto& x, const auto& y) {
    const auto x_letters = min(size_t{2}, x.size());
    string result{x.begin(), x.begin() + x_letters};
    const auto y_letters = min(size_t{3}, y.size());
    result.insert(result.end(), y.end() - y_letters, y.end());
    return result;
  };
  transform(words2.begin(), words2.end(), words3.begin(),
            back_inserter(result2), portmantize);
  REQUIRE(result2 == vector<string>{"lidar", "hubot", "brony", "qubit"});
}

TEST_CASE("swap_ranges") {
  vector<string> words1{"The", "king", "is", "dead."};
  vector<string> words2{"Long", "live", "the", "king."};
  swap_ranges(words1.begin(), words1.end(), words2.begin());
  REQUIRE(words1 == vector<string>{"Long", "live", "the", "king."});
  REQUIRE(words2 == vector<string>{"The", "king", "is", "dead."});
}

struct MoveDetector {
  MoveDetector() : owner{true} {}
  MoveDetector(const MoveDetector&) = delete;
  MoveDetector& operator=(const MoveDetector&) = delete;
  MoveDetector(MoveDetector&& o) = delete;
  MoveDetector& operator=(MoveDetector&& o) {
    o.owner = false;
    owner = true;
    return *this;
  }
  bool owner;
};

TEST_CASE("move_backward") {
  vector<MoveDetector> detectors1(2);
  vector<MoveDetector> detectors2(2);
  move_backward(detectors1.begin(), detectors1.end(), detectors2.end());
  REQUIRE_FALSE(detectors1[0].owner);
  REQUIRE_FALSE(detectors1[1].owner);
  REQUIRE(detectors2[0].owner);
  REQUIRE(detectors2[1].owner);
}

TEST_CASE("move") {
  vector<MoveDetector> detectors1(2);
  vector<MoveDetector> detectors2(2);
  move(detectors1.begin(), detectors1.end(), detectors2.begin());
  REQUIRE_FALSE(detectors1[0].owner);
  REQUIRE_FALSE(detectors1[1].owner);
  REQUIRE(detectors2[0].owner);
  REQUIRE(detectors2[1].owner);
}

TEST_CASE("copy_backward") {
  vector<string> words1{"A", "man", "a", "plan", "a", "bran", "muffin"};
  vector<string> words2{"a", "canal", "Panama"};
  const auto result =
      copy_backward(words2.cbegin(), words2.cend(), words1.end());
  REQUIRE(words1 ==
          vector<string>{"A", "man", "a", "plan", "a", "canal", "Panama"});
}

TEST_CASE("copy_n") {
  vector<string> words1{"on", "the", "wind"};
  vector<string> words2{"I'm", "a", "leaf"};
  copy_n(words1.cbegin(), words1.size(), back_inserter(words2));
  REQUIRE(words2 == vector<string>{"I'm", "a", "leaf", "on", "the", "wind"});
}

TEST_CASE("copy") {
  vector<string> words1{"and", "prosper"};
  vector<string> words2{"Live", "long"};
  copy(words1.cbegin(), words1.cend(), back_inserter(words2));
  REQUIRE(words2 == vector<string>{"Live", "long", "and", "prosper"});
}
