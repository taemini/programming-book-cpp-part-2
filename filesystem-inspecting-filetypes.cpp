#include <filesystem>
#include <iostream>

using namespace std;

void describe(const filesystem::path& p) {
  cout << boolalpha << "Path: " << p << endl;
  try {
    cout << "Is directory: " << filesystem::is_directory(p) << endl;
    cout << "Is regular file: " << filesystem::is_regular_file(p) << endl;
  } catch (const exception& e) {
    cerr << "Exception: " << e.what() << endl;
  }
}

int main() {
  filesystem::path nix_path{R"(/bin/bash)"};
  describe(nix_path);
  nix_path.remove_filename();
  describe(nix_path);
}