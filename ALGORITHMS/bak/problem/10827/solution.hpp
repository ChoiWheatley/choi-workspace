#ifndef SOLUTION
#define SOLUTION

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
using std::size_t;
using std::string;
using std::stringstream;
using std::vector;

static size_t decimal_point_pos(string const &num) {
  size_t dot_pos = num.find_first_of('.');
  if (dot_pos == string::npos) {
    return 0;
  }
  return num.size() - dot_pos - 1;
}

/**
 * @brief
 * 큰수 계산 구현하여 실수 곱하기 연산을 정수 곱하기 연산으로 변환하여 문제를
 * 풀어라!
 */
class BigNumber {
public:
  explicit BigNumber(string const &num)
      : m_decimal_point{decimal_point_pos(num)} {

    for (auto itr = num.crbegin(); itr != num.crend(); ++itr) {

      if (std::isdigit(*itr)) {
        m_digits.push_back((*itr) - '0');
      }
    }
  }

  BigNumber operator*(BigNumber const &rhs) {

    auto result = vector<int>(m_digits.size() + rhs.m_digits.size() - 1, 0);
    const size_t decimal_point = this->m_decimal_point + rhs.m_decimal_point;

    for (size_t i = 0; i < rhs.m_digits.size(); ++i) {

      auto r = rhs.m_digits[i];
      for (size_t j = 0; j < m_digits.size(); ++j) {

        auto l = m_digits[j];
        result[i + j] += r * l;
      }
    }

    return BigNumber(std::move(result), decimal_point);
  }

  /**
   * @brief converts to human-readable number format
   *
   * 유의사항, m_digits를 한 번 훑으면서 자릿수별로 10이 넘는 원소를 올림한다.
   */
  string to_string() {

    int roundup = 0;
    for (auto &digit : m_digits) {

      digit += roundup;
      roundup = digit / 10;
      digit = digit %= 10;
    }
    while (roundup > 0) {
      m_digits.push_back(roundup % 10);
      roundup /= 10;
    }

    stringstream ss;
    size_t point_count = m_digits.size();
    for (auto itr = m_digits.crbegin(); itr != m_digits.crend(); ++itr) {

      if (point_count == m_decimal_point) {

        ss << ".";
      }

      ss << static_cast<char>((*itr) + '0');
      point_count -= 1;
    }

    return ss.str();
  }

private:
  BigNumber(vector<int> &&digits, size_t decimal_point)
      : m_digits{std::move(digits)}, m_decimal_point(decimal_point) {}

  vector<int> m_digits;   // 10의 idx승번째 digit을 저장
  size_t m_decimal_point; // 소수자리수
};

#endif
