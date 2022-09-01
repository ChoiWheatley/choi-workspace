#include <array>
#include <cassert>
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace persona
{
  enum class Servey
  {
    RT,
    TR,
    FC,
    CF,
    MJ,
    JM,
    AN,
    NA,
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

  /// @brief 각 인덱스는 비트필드의 각 위치와도 매핑이 된다. 예를 들어 0b0101 = "RFJN"
  // const std::vector<std::map<uint8_t, char>> indexLookUp = {
  //     {{1, 'R'}, {0, 'T'}},
  //     {{1, 'C'}, {0, 'F'}},
  //     {{1, 'J'}, {0, 'M'}},
  //     {{1, 'A'}, {0, 'N'}},
  // };

  const std::vector<char> sameScoreLookUp = {
      {'R', 'C', 'J', 'A'}};

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
  };

} // namespace persona

string solution(vector<string> servey, vector<int> choices)
{
  auto answer = string{4, '\0'};
  persona::QuestionFactory factory;

  assert(servey.size() == choices.size());
  for (size_t i = 0; i < servey.size(); ++i)
  {
    auto *question = factory.getInstanceOf(servey[i]);
    question->Choice(static_cast<persona::Choices>(choices[i]));
  }

  auto arenaOfEachPersonality = std::map<persona::Servey, persona::Question::ScoreType>{};
  for (auto const *question : factory.getAllInstances())
  {
    auto const [iter, success] = arenaOfEachPersonality.insert({question->servey(), question->score()});
    assert(success);
    // TODO: TR vs RT, CF vs FC, NA vs AN, JM vs MJ 격돌시켜서 승자 뽑아내기
  }

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