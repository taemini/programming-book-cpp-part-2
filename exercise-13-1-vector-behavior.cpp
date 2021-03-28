#include <cstdio>
#include <vector>

int main() {
  std::vector<unsigned long> v{};
  printf("capacity of v : %zu\n", v.capacity());
  printf("size of v: %zu\n", v.size());
  printf("max_size of v : %zu\n\n", v.max_size());

  v.reserve(10);
  printf("capacity of v : %zu\n", v.capacity());
  printf("size of v: %zu\n", v.size());
  printf("max_size of v : %zu\n\n", v.max_size());

  for (size_t i{}; i < 20; i++) {
    if (i == 0 || i == 1) {
      v.push_back(1);
    } else {
      v.push_back(v[i - 2] + v[i - 1]);
    }
  }
  printf("capacity of v : %zu\n", v.capacity());
  printf("size of v: %zu\n", v.size());
  printf("max_size of v : %zu\n\n", v.max_size());

  for (auto num : v) {
    printf("%lu ", num);
  }
}