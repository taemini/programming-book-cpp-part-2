#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  istreambuf_iterator<char> cin_itr{cin.rdbuf()}, end{};
  cout << "What is your name? ";
  const string name{cin_itr, end};
  cout << "\nGoodbye, " << name;
}