#include <array>
#include <cstdio>

int main() {
  unsigned long maximum{0};
  std::array<unsigned long, 5> values{10, 50, 20, 40, 0};
  for (auto value : values) {
    if (maximum < value) {
      maximum = value;
    }
  }
  printf("The maximum value is %lu\n", maximum);
}