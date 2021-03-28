#include <cstdio>
#include <regex>

int main(int argc, char** argv) {
  size_t vowels_count{};
  std::string str{};
  for (size_t i{1}; i < argc; i++) {
    str += argv[i];
  }
  std::regex vowels{R"([aeiou])"};
  for (char letter : str) {
    if (std::regex_match(std::string{letter}, vowels)) {
      vowels_count++;
    }
  }
  printf("vowels count : %zu", vowels_count);
}