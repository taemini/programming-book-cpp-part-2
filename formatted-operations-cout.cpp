#include <bitset>
#include <iostream>
#include <string>

using namespace std;

int main() {
  bitset<8> s{"01110011"};
  string str("Crying zeros and I'm hearing ");
  size_t num{111};
  cout << s;      // bitset
  cout << '\n';   // char
  cout << str;    // string
  cout << num;    // size_t
  cout << "s\n";  // C-style (null-terminated) string
};