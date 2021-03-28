// unordered map이었으면 좀 더 좋았을 듯...
#include <cstdio>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

constexpr char pos_A{'A'}, pos_Z{'Z'}, pos_a{'a'}, pos_z{'z'};

struct AlphaHistogram {
  void ingest(std::string_view str_view);
  void print();

 private:
  std::vector<size_t> counts = std::vector<size_t>(26, 0);
};

void AlphaHistogram::ingest(std::string_view str_view) {
  std::regex upper_regex{R"([A-Z])"};
  std::regex lower_regex{R"([a-z])"};
  for (char letter : str_view) {
    if (std::regex_match(std::string{letter}, upper_regex)) {
      counts[letter - pos_A]++;
    } else if (std::regex_match(std::string{letter}, lower_regex)) {
      printf("(%c %d)", letter, letter - pos_a);
      counts[letter - pos_a]++;
    } else {
      // do nothing
    }
  }
  printf("\n");
  printf("end of for...\n");
}

void AlphaHistogram::print() {
  char index{};
  for (size_t count : counts) {
    printf("%c: ", index + pos_A);
    while (count--) {
      printf("*");
    }
    printf("\n");
    index++;
  }
}

int main(int argc, char** argv) {
  AlphaHistogram histo{};
  std::string input{};
  for (size_t i{1}; i < argc; i++) {
    input += argv[i];
  }
  printf("your input : %s\n", input.c_str());
  histo.ingest(input);
  histo.print();
}