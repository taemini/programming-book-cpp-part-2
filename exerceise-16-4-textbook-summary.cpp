#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

constexpr char pos_A{'A'}, pos_Z{'Z'}, pos_a{'a'}, pos_z{'z'};

struct AlphaHistogram {
  void ingest(std::string_view str_view);
  void print();

 private:
  std::vector<size_t> counts = std::vector<size_t>(26, 0);
};

void AlphaHistogram::ingest(std::string_view str_view) {
  std::regex upper_regex{R"([A-Z])"};
  std::regex lower_regex{R"([a-z])"};
  for (char letter : str_view) {
    if (std::regex_match(std::string{letter}, upper_regex)) {
      counts[letter - pos_A]++;
    } else if (std::regex_match(std::string{letter}, lower_regex)) {
      counts[letter - pos_a]++;
    } else {
      // do nothing
    }
  }
}

void AlphaHistogram::print() {
  char index{};
  for (size_t count : counts) {
    printf("%c: ", index + pos_A);
    while (count--) {
      printf("*");
    }
    printf("\n");
    index++;
  }
}

ifstream open(const char* path, ios_base::openmode mode = ios_base::in) {
  ifstream file{path, mode};
  if (!file.is_open()) {
    string err_msg{"Unable to open file "};
    err_msg.append(path);
    throw runtime_error{err_msg};
  }

  return file;
}

int main() {
  string word{};
  size_t w_length_sum{};
  size_t w_count{};
  AlphaHistogram histo;
  auto file = open("exercise-16-4-textbook.txt");

  while (file >> word) {
    w_count++;
    w_length_sum += word.size();
    histo.ingest(word);
  }

  cout << "Word count: " << w_count << endl;
  cout << "Average word length: " << w_length_sum / w_count << endl;
  histo.print();
  // string buffer로 file stream buffer string으로 받아내기
  // ostringstream oss;
  // oss << file.rdbuf();
  // string input{oss.str()};
  // cout << input << endl;

  // stream buffer iterator로 file stream buffer string으로 받아내기
  // istreambuf_iterator<char> begin{file}, end{};
  // string input{begin, end};
  // cout << input << endl;

  // 음... 전체를 한꺼번에 받아내는 것보다
  // 점진적으로 받아내는 것이 더 좋겠군...
}