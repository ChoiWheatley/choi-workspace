#include <gtest/gtest.h>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/// @brief simply contains two strings, reporting id and be reported id
struct Report
{
  string id;
  string to;
  bool operator==(const Report &other) const
  {
    return (id == other.id && to == other.to);
  }

  bool operator<(const Report &other) const
  {
    if (id == other.id)
    {
      return (to < other.to);
    }
    return (id < other.id);
  }

  Report(string id, string to) : id{id}, to{to} {}
}; // struct Report

/// @brief Parse string that contains reporter and reportee splitted by whitespace
/// @param str 'a b' means `a` reported `b`
static auto ParseReport(const string &str) -> Report
{
  auto words = vector<string>{};
  auto input_stream = istringstream{str};
  for (string word; std::getline(input_stream, word, ' ');)
  {
    words.push_back(word);
  }
  return Report{words[0], words[1]};
}

static auto solution(vector<string> id_list, vector<string> report, int k) -> vector<int>
{
  map<string, size_t> const index_map = // Key: id, Value: id_list에서 id의 인덱스
      [&id_list]
  {
    map<string, size_t> ret;
    for (size_t idx = 0; idx < id_list.size(); ++idx)
    {
      ret.insert({id_list[idx], idx});
    }
    return ret;
  }();
  map<string, set<string>> reporteeTbl; // Key: 신고당한 사람, Value: 그 사람을 신고한 사람들의 집합
  map<string, set<string>> reporterTbl; // Key: 신고한 사람, Value: 그 사람이 신고한 사람들의 집합

  // table init
  for (auto const &i : id_list)
  {
    reporteeTbl[i] = {};
    reporterTbl[i] = {};
  }

  // make report clear
  set<Report> const reports = [&report]
  {
    set<Report> ret;
    for (auto const &i : report)
    {
      auto const r = ParseReport(i);
      ret.insert(r);
    }
    return ret;
  }();

  // insert report cases
  for (auto const &i : reports)
  {
    reporteeTbl[i.to].insert(i.id);
    reporterTbl[i.id].insert(i.to);
  }

  auto ret = vector<int>(static_cast<int>(id_list.size()));
  for (auto const &[reporter, reportees] : reporterTbl)
  {
    for (auto const &reportee : reportees)
    {
      if (reporteeTbl[reportee].size() >= k)
      {
        ret.at(index_map.at(reporter)) += 1;
      }
    }
  }
  return ret;
}

namespace testing
{
  class ReportFixtureRe : public Test
  {
  protected:
    static constexpr size_t MIN_ID_LIST_SIZE = 2;
    static constexpr size_t MAX_ID_LIST_SIZE = 1000;
    static constexpr size_t MIN_ID_SIZE = 1;
    static constexpr size_t MAX_ID_SIZE = 10;
    static constexpr size_t MIN_REPORT_SIZE = 1;
    static constexpr size_t MAX_REPORT_SIZE = 200000;
    static constexpr size_t MIN_REPORT_STR_SIZE = 3;
    static constexpr size_t MAX_REPORT_STR_SIZE = 21;
    static constexpr size_t MIN_K = 1;
    static constexpr size_t MAX_K = 200;

    vector<string> id_list;
    vector<string> report;
    int k;
    vector<int> result;

    auto DoTest() -> void
    {
      ASSERT_GE(id_list.size(), MIN_ID_LIST_SIZE);
      ASSERT_LE(id_list.size(), MAX_ID_LIST_SIZE);
      set<string> id_set;
      for (const auto &id : id_list)
      {
        ASSERT_GE(id.size(), MIN_ID_SIZE);
        ASSERT_LE(id.size(), MAX_ID_SIZE);
        // no duplicated elements
        auto [iter, success] = id_set.insert(id);
        ASSERT_TRUE(success);
      }

      ASSERT_GE(report.size(), MIN_REPORT_SIZE);
      ASSERT_LE(report.size(), MAX_REPORT_SIZE);
      for (const auto &each : report)
      {
        ASSERT_GE(each.size(), MIN_REPORT_STR_SIZE);
        ASSERT_LE(each.size(), MAX_REPORT_STR_SIZE);
        // only two splitted words
        set<string> words;
        auto input = istringstream{each};
        for (string word; std::getline(input, word, ' ');)
        {
          ASSERT_NE(id_set.find(word), id_set.end());
          words.insert(word);
        }
        ASSERT_EQ(words.size(), 2) << "Each report must have exactly two words!";
      }

      ASSERT_GE(k, MIN_K);
      ASSERT_LE(k, MAX_K);

      ASSERT_EQ(result.size(), id_list.size());

      auto const answer = solution(id_list, report, k);
      EXPECT_EQ(result, answer);
    }
  }; // class Fixture

  TEST_F(ReportFixtureRe, 1)
  {
    id_list = {"muzi", "frodo", "apeach", "neo"};
    report = {"muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi"};
    k = 2;
    result = {2, 1, 1, 0};

    DoTest();
  }

  /// ryan이 con을 4번 신고했으나 한 유저가 같은 유저를 여러 번 신고한 경우는 1회로 처리한다.
  TEST_F(ReportFixtureRe, 2)
  {
    id_list = {"con", "ryan"};
    report = {"ryan con", "ryan con", "ryan con", "ryan con"};
    k = 3;
    result = {0, 0};

    DoTest();
  }

  TEST_F(ReportFixtureRe, 3)
  {
    id_list = {"a", "b", "c"};
    report = {"a b", "c b"};
    k = 2;
    result = {1, 0, 1};

    DoTest();
  }

  TEST_F(ReportFixtureRe, 4)
  {
    id_list = {"a", "b", "c", "d", "e", "f"};
    report = {"a b", "c b", "d b", "e b", "f b", "a c", "b c"};
    k = 2;
    result = {2, 1, 1, 1, 1, 1};

    DoTest();
  }

  TEST_F(ReportFixtureRe, 5)
  {
    id_list = {"a", "b", "c", "d", "e", "f"};
    report = {"a f", "c f", "d f", "e f", "f b", "a f", "b f"};
    k = 2;
    result = {1, 1, 1, 1, 1, 0};

    DoTest();
  }

  TEST_F(ReportFixtureRe, ReportSizeBoundary)
  {
    id_list = {"a", "b"};
    for (size_t i = 0; i < MAX_REPORT_SIZE; ++i)
    {
      report.push_back({"a b"});
    }
    k = 2;
    result = {0, 0};

    DoTest();
  }

} // namespace testing