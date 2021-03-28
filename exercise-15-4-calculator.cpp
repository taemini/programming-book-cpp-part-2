#include <cstdio>
#include <deque>
#include <queue>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

const std::regex numeric_regex{R"([0-9]+)"};

std::string remove_useless_characters(const std::string& input) {
  std::regex meaningless_characters_regex{R"([^+\-*/()0-9])"};
  return std::regex_replace(input, meaningless_characters_regex, "");
}
size_t level_of_op_in_stack(const std::string& op) {
  std::regex plus_minus_regex{R"([+-])"};
  if (op == "(") {
    return 0;
  } else if (std::regex_match(op, plus_minus_regex)) {
    return 1;
  }
  // * / %
  return 2;
}
std::vector<std::string> infix_to_postfix(const std::string& input) {
  std::vector<std::string> tokenized{};
  std::vector<std::string> postfix{};
  std::stack<std::string> stack{};

  auto remain = input.substr();
  while (remain.size() > 0) {
    auto index = remain.find_first_of("+-*/()");
    if (index > 0) {  // tokenize number
      tokenized.push_back(remain.substr(0, index));
      remain.replace(0, index, "");
    }  // tokenize operator
    if (index != std::string::npos) {
      tokenized.push_back(remain.substr(0, 1));
      remain.replace(0, 1, "");
    }
  }
  for (auto elem : tokenized) {
    if (std::regex_match(elem, numeric_regex)) {
      // elem is number
      postfix.push_back(elem);
    } else {
      // elem is operator
      if (elem == "(") {
        stack.push("(");
      } else if (elem == ")") {
        while (stack.top() != "(") {
          postfix.push_back(stack.top());
          stack.pop();
        }
        stack.pop();  // pop "("
      } else if (stack.size() == 0 || level_of_op_in_stack(stack.top()) <
                                          level_of_op_in_stack(elem)) {
        stack.push(elem);
      } else {
        while (stack.size() > 0 && level_of_op_in_stack(stack.top()) >=
                                       level_of_op_in_stack(elem)) {
          postfix.push_back(stack.top());
          stack.pop();
        }
        stack.push(elem);
      }
    }
  }
  while (stack.size() > 0) {
    postfix.push_back(stack.top());
    stack.pop();
  }
  return postfix;
}

double calculate_postfix(const std::vector<std::string>& postfix) {
  std::stack<double> stack{};
  for (auto elem : postfix) {
    if (std::regex_match(elem, numeric_regex)) {
      stack.push(std::stod(elem));
    } else {
      double a = stack.top();
      stack.pop();
      double b = stack.top();
      stack.pop();
      if (elem == "+") {
        stack.push(a + b);
      } else if (elem == "-") {
        stack.push(a - b);
      } else if (elem == "*") {
        stack.push(a * b);
      } else if (elem == "/") {
        stack.push(a / b);
      } else {
        // throw std::runtime_error{std::string{"Unrecognized operator "} +
        // elem};
      }
    }
  }
  return stack.top();
}

int main(int argc, char** argv) {
  std::string raw_input;
  for (size_t i{1}; i < argc; i++) {
    raw_input += argv[i];
  }
  const auto input = remove_useless_characters(raw_input);
  const auto postfix = infix_to_postfix(input);
  printf("[postfix] : ");
  for (auto elem : postfix) {
    printf("%s ", elem.c_str());
  }
  printf("\n");
  printf("[result] : %g\n", calculate_postfix(postfix));
}