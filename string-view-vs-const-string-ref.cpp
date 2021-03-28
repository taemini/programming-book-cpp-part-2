#include <cstdio>
#include <string>
#include <string_view>

size_t count_vees_view(std::string_view my_view) {
  size_t result{};
  for (auto letter : my_view)
    if (letter == 'v') result++;
  return result;
}

size_t count_vees_ref(const std::string& my_view) {
  size_t result{};
  for (auto letter : my_view)
    if (letter == 'v') result++;
  return result;
}

int main() {
  const char* c_str = "vee is bee is vee is bee is vvveee";
  std::string str("vee is bee is vee is bee is vvveee");

  // same
  printf("%zu\n", count_vees_view(str));
  printf("%zu\n", count_vees_ref(str));

  // view is better
  printf("%zu\n", count_vees_view(c_str));  // std::string construction X
  printf("%zu\n", count_vees_ref(c_str));   // std::string contruction O
}