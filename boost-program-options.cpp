#include <boost/program_options.hpp>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  using namespace boost::program_options;
  bool is_recursive{}, is_help{};

  options_description description{"mgrep [options] pattern path1 path2 ..."};
  description.add_options()
    ("help,h", bool_switch(&is_help), "display a help dialog")
    ("threads,t", value<int>()->default_value(4), "number of threads to use")
    ("recursive,r", bool_switch(&is_recursive), "search subdirectories recursively")
    ("pattern", value<std::string>(), "pattern to search for")
    ("paths", value<std::vector<std::string>>(), "path to search");
  std::cout << description;
}