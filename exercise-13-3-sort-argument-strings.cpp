#include <cstdio>
#include <set>
#include <stdexcept>

int main(int argc, char** argv) {
  auto cmp = [](char* a, char* b) {
    size_t index{};
    while (a[index] && b[index]) {
      if (a[index] < b[index]) {
        return true;
      } else if (a[index] > b[index]) {
        return false;
      }
      index++;
      continue;
    }
    if (b[index]) {
      return true;
    }
    return false;
  };
  std::set<char*, decltype(cmp)> values{cmp};

  if (argc <= 1) {
    throw std::runtime_error{"Too few arguments"};
  }

  for (size_t i{}; i < argc - 1; i++) {
    values.insert(argv[i + 1]);
  }
  printf("%zu\n", values.size());
  for (char* str : values) {
    printf("%s\n", str);
  }
}