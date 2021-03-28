#include <boost/algorithm/string/case_conv.hpp>
#include <cstdio>
#include <regex>
#include <string>

int main(int argc, char** argv) {
  std::string input{};
  for (size_t i{1}; i < argc; i++) {
    input += argv[i];
  }
  std::regex not_alpha_regex{R"([^a-zA-Z])"};
  const auto only_alpha = std::regex_replace(input, not_alpha_regex, "");
  auto only_lowercase = boost::algorithm::to_lower_copy(only_alpha);
  auto reversed = only_lowercase.substr();

  const size_t half_n = only_lowercase.size() / 2;
  const size_t full_n = only_lowercase.size();

  auto begin = reversed.begin();
  auto end = only_lowercase.end();
  for (size_t i{}; i < half_n; i++) {
    reversed.replace(begin, begin + 1, end - 1, end);
    begin++;
    end--;
  }
  printf("\"%s\" is palindrome : %s", input.c_str(),
         only_lowercase == reversed ? "true" : "false");
}