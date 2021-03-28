#include <filesystem>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  const filesystem::path kernel32{
      R"(/Users/tamini/study/cpp/crash-course-part-2/filesystem-path-decomposition.cpp)"};
  cout << "Root name: " << kernel32.root_name()
       << "\nRoot directory: " << kernel32.root_directory()
       << "\nRoot path: " << kernel32.root_path()
       << "\nRelative path: " << kernel32.relative_path()
       << "\nParent path: " << kernel32.parent_path()
       << "\nFilename: " << kernel32.filename() << "\nStem: " << kernel32.stem()
       << "\nExtension: " << kernel32.extension() << endl;
}
