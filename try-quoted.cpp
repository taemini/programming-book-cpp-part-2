#include <iomanip>
#include <iostream>
#include <sstream>

int main() {
  std::cout << std::quoted("hello \\ world") << std::endl;
  std::cout << "hello \\ world" << std::endl;
}