#include <boost/algorithm/string/case_conv.hpp>
#include <iostream>
#include <string>

using namespace std;

int main() {
  istreambuf_iterator<char> begin{cin.rdbuf()}, end{};
  string input{begin, end};
  boost::algorithm::to_upper(input);
  cout << input << endl;
}