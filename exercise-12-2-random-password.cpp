#include <random>

int main() {
  const size_t PASS_LENGTH = 10;
  char pass[PASS_LENGTH + 1]{};
  std::random_device rd_device{};
  std::uniform_int_distribution<int> dist{0, 35};
  char possible_characters[]{'0', '1', '2', '3', '4', '5', '6', '7', '8',
                             '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                             'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                             'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  const size_t characters_num = sizeof(possible_characters) / sizeof(char);
  for (size_t i = 0; i < PASS_LENGTH; i++) {
    pass[i] = possible_characters[dist(rd_device)];
  }
  printf("%s\n", pass);
}
