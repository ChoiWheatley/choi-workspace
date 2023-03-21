#ifndef SOLUTION
#define SOLUTION

#include <cstddef>
#include <string>
#include <vector>
using std::string;
using std::vector;

#define cr const &

namespace kmp_helper {
inline vector<size_t> to_backtrace(string cr pat) {
  vector<size_t> ret(pat.size());
  size_t j = 0;
  for (size_t i = 1; i < pat.size(); ++i) {
    // not match
    while (j > 0 && pat[i] != pat[j]) {
      j = ret[j - 1];
    }
    // does match character
    if (pat[i] == pat[j]) {
      j += 1;
      ret[i] = j;
    }
  }
  return ret;
}
} // namespace kmp_helper

class Kmp {
public:
  explicit Kmp(string &&pattern)
      : m_pattern(std::move(pattern)),
        m_backtrace(kmp_helper::to_backtrace(m_pattern)) {}

  template <class UnaryFn>
  void find(string cr other, UnaryFn cr on_find) const {
    size_t j = 0;
    for (size_t i = 0; i < other.size(); ++i) {
      // not match
      while (j > 0 && other[i] != m_pattern[j]) {
        j = m_backtrace[j - 1]; // j - 1번째에는 맞췄겠지
      }
      // does match character
      if (other[i] == m_pattern[j]) {
        if (j == m_pattern.size() - 1) {
          // does match word
          auto start_idx = i - j;
          on_find(start_idx);
          j = m_backtrace[j]; // 계속 j가 증가하는 것을 막기위해
        } else {
          j += 1;
        }
      }
    }
  }

private:
  const string m_pattern;
  const vector<size_t> m_backtrace;
};

#undef cr
#endif
