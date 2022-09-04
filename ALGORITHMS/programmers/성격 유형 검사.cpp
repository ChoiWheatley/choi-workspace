#include <array>
#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace persona
{
  enum class Servey : char
  {
    RT = 'T',
    TR = 'R',
    FC = 'C',
    CF = 'F',
    MJ = 'J',
    JM = 'M',
    AN = 'N',
    NA = 'A',
  };

  auto indexOf(Servey s) -> size_t
  {
    switch (s)
    {
    case Servey::RT:
    case Servey::TR:
      return 0;
    case Servey::FC:
    case Servey::CF:
      return 1;
    case Servey::MJ:
    case Servey::JM:
      return 2;
    case Servey::AN:
    case Servey::NA:
      return 3;
    }
  }

  auto sameScoreLookUp(Servey s) -> char
  {
    switch (s)
    {
    case Servey::RT:
    case Servey::TR:
      return 'R';
    case Servey::FC:
    case Servey::CF:
      return 'C';
    case Servey::MJ:
    case Servey::JM:
      return 'J';
    case Servey::AN:
    case Servey::NA:
      return 'A';
    }
  }

  /// @brief servey string의 원소는 "RT" 와 같이 두 개의 char로 이루어져 있다.
  /// 첫번째 char는 비동의 관련 선택지를 선택하면 받는 성격유형이다.
  /// 두번째 char는 동의 관련 선택지를 선택하면 받는 성격유형이다.
  const std::map<string, Servey> serveyLookUp = {
      {"RT", Servey::RT},
      {"TR", Servey::TR},
      {"FC", Servey::FC},
      {"CF", Servey::CF},
      {"MJ", Servey::MJ},
      {"JM", Servey::JM},
      {"AN", Servey::AN},
      {"NA", Servey::NA},
  };

  enum class Choices
  {
    VERY_NEGATIVE = 1,
    NEGATIVE = 2,
    LITTLE_NEGATIVE = 3,
    DONT_KNOW = 4,
    LITTLE_POSITIVE = 5,
    POSITIVE = 6,
    VERY_POSITIVE = 7,
  };

  // <<interface>>
  // 단일 지표에 대한 정보를 다룬다.
  class Question
  {
  public:
    using ScoreType = int16_t;
    using IndexType = size_t;

    /// @brief 지표 하나에 대한 점수를 반환합니다.
    /// @return 양수이면 `indexLookUp`에서 1에 해당하는 유형의 점수가 더 높다. vice versa.
    ///         0이면 두 성격 유형의 알파벳 중 빠른 성격 유형을 선택한다.
    virtual auto score() const -> ScoreType = 0;

    /// @brief Servey 값을 알려준다.
    virtual auto servey() const -> Servey = 0;

    /// @brief 결과값의 위치를 알려준다.
    virtual auto idxPosition() const -> IndexType = 0;

    /// @brief 상태를 변경하는 메서드.
    /// @param Choice 질문의 선택지
    virtual auto Choice(Choices) -> void = 0;
  }; // class Question

  /// @brief <<interface>> 공통된 메서드만 구현함.
  class CommonQuestion : public Question
  {
    int16_t score_ = 0;

  public:
    auto score() const -> int16_t override { return score_; }
    auto Choice(Choices choice) -> void override
    {
      static auto constexpr mediumChoice = static_cast<int16_t>(Choices::DONT_KNOW);
      auto const choiceInt = static_cast<int16_t>(choice);
      score_ = score_ + choiceInt - mediumChoice;
    }
    auto idxPosition() const -> size_t override
    {
      return indexOf(servey());
    }
  };

  class RTQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::RT; }
  };

  class TRQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::TR; }
  };

  class CFQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::CF; }
  };

  class FCQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::FC; }
  };

  class JMQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::JM; }
  };

  class MJQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::MJ; }
  };

  class ANQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::AN; }
  };

  class NAQuestion : public CommonQuestion
  {
  public:
    auto servey() const -> Servey override { return Servey::NA; }
  };

  /// @brief Dependency Injection
  class QuestionFactory
  {
    RTQuestion rtq_;
    TRQuestion trq_;
    CFQuestion cfq_;
    FCQuestion fcq_;
    JMQuestion jmq_;
    MJQuestion mjq_;
    ANQuestion anq_;
    NAQuestion naq_;
    vector<Question *> allInstances_{{&rtq_, &trq_, &cfq_, &fcq_, &jmq_, &mjq_, &anq_, &naq_}};

  public:
    auto getInstanceOf(Servey servey) -> Question *
    {
      for (auto *i : allInstances_)
      {
        if (i->servey() == servey)
        {
          return i;
        }
      }
      return nullptr;
    }

    auto getInstanceOf(string servey) -> Question *
    {
      auto const searchResult = serveyLookUp.find(servey);
      assert(searchResult != serveyLookUp.end());
      return getInstanceOf(searchResult->second);
    }

    auto getAllInstances() -> const vector<Question *> &
    {
      return allInstances_;
    }
  }; // class QuestionFactory

  // TR vs RT, CF vs FC, NA vs AN, JM vs MJ 격돌시켜서 승자 뽑아내기
  auto compare(const Question &a, const Question &b) -> char
  {
    // TODO: problem
    char retval = '\0';
    if (a.score() < b.score())
    {
      retval = static_cast<char>(b.servey());
    }
    else if (a.score() > b.score())
    {
      retval = static_cast<char>(a.servey());
    }
    else
    {
      retval = sameScoreLookUp(a.servey());
    }
    return retval;
  }
} // namespace persona

string solution(vector<string> servey, vector<int> choices)
{
  using namespace persona;

  auto answer = string{};
  std::cerr << "\t" << answer << "\t\n";
  QuestionFactory factory;

  assert(servey.size() == choices.size());
  for (size_t i = 0; i < servey.size(); ++i)
  {
    auto *question = factory.getInstanceOf(servey[i]);
    question->Choice(static_cast<Choices>(choices[i]));
  }

#if CMAKE_BUILD_TYPE == DEBUG
  // DEBUG: show all scores without comparing
  for (auto const *inst : factory.getAllInstances())
  {
    std::cerr << static_cast<char>(inst->servey()) << ": " << inst->score() << "\n";
  }
#endif // DEBUG

  answer.insert(answer.end(),
                compare(
                    *factory.getInstanceOf(Servey::RT),
                    *factory.getInstanceOf(Servey::TR)));
  answer.insert(answer.end(),
                compare(
                    *factory.getInstanceOf(Servey::CF),
                    *factory.getInstanceOf(Servey::FC)));
  answer.insert(answer.end(),
                compare(
                    *factory.getInstanceOf(Servey::JM),
                    *factory.getInstanceOf(Servey::MJ)));
  answer.insert(answer.end(),
                compare(
                    *factory.getInstanceOf(Servey::AN),
                    *factory.getInstanceOf(Servey::NA)));
  std::cout << answer << "\n";

  return answer;
}

class Personality : public ::testing::Test
{
protected:
  vector<string> servey;
  vector<int> choices;

  string
  DoTest() const
  {
    return solution(servey, choices);
  }
}; // class Example

TEST_F(Personality, Case1)
{
  servey = vector<string>{
      {"AN"},
      {"CF"},
      {"MJ"},
      {"RT"},
      {"NA"},
  };
  choices = vector<int>{{5, 3, 2, 7, 5}};
  auto const result = "TCMA";

  EXPECT_EQ(result, DoTest());
}

TEST_F(Personality, Case2)
{
  servey = vector<string>{
      {"TR"},
      {"RT"},
      {"TR"},
  };
  choices = vector<int>{{7, 1, 3}};
  auto const result = "RCJA";

  EXPECT_EQ(result, DoTest());
}