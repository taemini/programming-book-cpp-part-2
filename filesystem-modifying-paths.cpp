#include <filesystem>
#include <iostream>

using namespace std;

int main() {
  filesystem::path path{
      R"(/Users/tamini/study/cpp/crash-course-part-2/filesystem-path-decomposition.cpp)"};
  cout << path << endl;

  path.make_preferred();
  cout << path << endl;

  path.replace_filename("win32kfull.sys");
  cout << path << endl;

  path.remove_filename();
  cout << path << endl;

  path.clear();
  cout << "Is empty: " << boolalpha << path.empty() << endl;
}