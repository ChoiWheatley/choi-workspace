
#include <cstddef>
#include <string>
#include <vector>
using std::string;
using std::vector;

#define cr const &

// helper for Kmp

static vector<size_t> preprocess(string cr pattern) {
  auto result = vector<size_t>(pattern.size());
  size_t j = 0;
  for (size_t i = 1; i < pattern.size(); ++i) {
    while (j > 0 && pattern[i] != pattern[j]) {
      // backtrace until adequate
      j = result[j - 1];
    }
    if (pattern[i] == pattern[j]) {
      // match one character
      j += 1;
      result[i] = j;
    }
  }
  return result;
}

class Kmp {

private:
  const vector<size_t> m_backtrace;
  const string m_pattern;

public:
  explicit Kmp(string &&p)
      : m_backtrace(preprocess(p)), m_pattern(std::move(p)) {}

  template <class UnaryFn>
  void compare_to(string cr other, UnaryFn cr on_match) const {
    size_t j = 0;
    for (size_t i = 0; i < other.size(); ++i) { // i 는 계속 증가
      while (j > 0 && other[i] != m_pattern[j]) {
        // unmatch
        j = m_backtrace[j - 1];
      }
      if (other[i] == m_pattern[j]) {
        // match one character
        if (j == m_pattern.size() - 1) {
          // match whole pattern
          on_match(i - j);
          j = m_backtrace[j]; // 더 볼 필요가 없기 때문에 j를 현재 위치에서 fail
                              // 시킨다.
        } else {
          j += 1;
        }
      }
    }
  }
};