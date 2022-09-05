/// https://school.programmers.co.kr/learn/courses/30/lessons/92334
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using index_t = size_t;
using IndexMap = unordered_map<string /*id*/, index_t /*idx*/>;

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

struct ReportWithIdx : public Report
{
  index_t id_idx;
  index_t to_idx;
  bool operator==(const ReportWithIdx &other) const
  {
    return (id == other.id && to == other.to) &&
           (id_idx == other.id_idx && to_idx == other.to_idx);
  }
  ReportWithIdx(string id, index_t id_idx, string to, index_t to_idx)
      : Report{id, to}, id_idx{id_idx}, to_idx{to_idx} {}
}; // ReportWithIdx

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

static auto MakeIndexMap(const vector<string> &id_list) -> IndexMap
{
  IndexMap ret;
  for (index_t idx = 0; idx < id_list.size(); ++idx)
  {
    ret.insert({id_list[idx], idx});
  }
  return ret;
}

static auto MakeReportSet(const vector<string> &report) -> set<Report>
{
  set<Report> ret;
  for (auto const &r : report)
  {
    ret.insert({ParseReport(r)});
  }
  return ret;
}

static auto MakeReportWithIdx(const set<Report> &reports, const IndexMap &indexMap) -> set<ReportWithIdx>
{
  set<ReportWithIdx> ret;
  for (Report const &r : reports)
  {
    ret.insert(ReportWithIdx{
        r.id, indexMap.at(r.id),
        r.to, indexMap.at(r.to)});
  }
  return ret;
}

static auto CountReports(const IndexMap &indexMap, const set<ReportWithIdx> &reportWithIdx) -> vector<size_t>
{
  auto ret = vector<size_t>(static_cast<int>(indexMap.size()), 0);
  for (auto const &r : reportWithIdx)
  {
    ret.at(r.to_idx) += 1;
  }
  return ret;
}

template <typename _T>
static auto filter(const vector<_T> &list, std::function<bool(const _T &)> condition) -> vector<_T>
{
  vector<_T> ret;
  for (auto const &each : list)
  {
    if (condition(each))
    {
      ret.push_back(each);
    }
  }
  return ret;
}

static vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
  auto answer = vector<int>(static_cast<int>(id_list.size()), 0);

  IndexMap const indexMap = MakeIndexMap(id_list);

  set<Report> const reports = MakeReportSet(report);

  set<ReportWithIdx> const reportWithIdx = MakeReportWithIdx(reports, indexMap);

  vector<size_t> const countReports = CountReports(indexMap, reportWithIdx);

  auto const badUsersList = [&countReports, &k]() -> vector<index_t>
  {
    vector<index_t> ret;
    for (index_t i = 0; i < countReports.size(); ++i)
    {
      if (k <= countReports[i])
      {
        ret.push_back(i);
      }
    }
    return ret;
  }();

  auto const badUsersSet = set<index_t>{badUsersList.begin(), badUsersList.end()};

  for (auto const &report : reportWithIdx)
  {
    auto const badUser = badUsersSet.find(report.to_idx);
    if (badUser != badUsersSet.end())
    {
      answer.at(report.id_idx) += 1;
    }
  }

  return answer;
}

namespace testing
{
  TEST(신고결과받기, ParseReport)
  {
    auto const str = "muzi frodo";
    auto const ans = Report{"muzi", "frodo"};
    EXPECT_EQ(ans, ParseReport(str));
  }

  TEST(신고결과받기, Filter)
  {
    auto const vec = []() -> vector<int>
    {
      vector<int> ret;
      for (int i = 0; i < 100; ++i)
      {
        ret.push_back(i);
      }
      return ret;
    }();

    auto const ans = []() -> vector<int>
    {
      vector<int> ret;
      for (int i = 0; i < 100; ++i)
      {
        if ((i % 2) == 0)
        {
          ret.push_back(i);
        }
      }
      return ret;
    }();

    EXPECT_EQ(
        filter<int>(
            vec,
            [](const int &elem)
            { return (elem % 2) == 0; }),
        ans);
  }

  TEST(신고결과받기, IndexMap)
  {
    auto const str = vector<string>{
        {"a"},
        {"b"},
        {"c"},
        {"d"},
        {"e"},
        {"f"},
    };
    auto const ans = IndexMap{
        {"a", 0},
        {"b", 1},
        {"c", 2},
        {"d", 3},
        {"e", 4},
        {"f", 5},
    };
    EXPECT_EQ(MakeIndexMap(str), ans);
  }

  TEST(신고결과받기, MakeReportSet)
  {
    auto const report = vector<string>{
        {"a b"},
        {"a c"},
        {"a d"},
        {"a e"},
        {"b a"},
        {"b c"},
        {"c d"},
        {"f d"},
        {"f d"},
        {"e d"},
        {"e d"},
    };

    auto const ans = set<Report>{
        Report{"a", "c"},
        Report{"a", "d"},
        Report{"a", "e"},
        Report{"b", "a"},
        Report{"c", "d"},
        Report{"f", "d"},
        Report{"f", "d"},
        Report{"b", "c"},
        Report{"e", "d"},
        Report{"e", "d"},
        Report{"a", "b"},
    };

    auto const ret = MakeReportSet(report);
    EXPECT_EQ(ret.size(), ans.size());
    EXPECT_EQ(ret, ans);
  }

  class ReportFixture : public Test
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

  // TEST_F(ReportFixture, WrongTestCase)
  // {
  //   id_list = {"a", "b", "c"};
  //   report = {"a d"};
  //   k = 3;
  //   result = {0, 0, 0};

  //   DoTest();
  // }

  TEST_F(ReportFixture, 1)
  {
    id_list = {"muzi", "frodo", "apeach", "neo"};
    report = {"muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi"};
    k = 2;
    result = {2, 1, 1, 0};

    DoTest();
  }

  /// ryan이 con을 4번 신고했으나 한 유저가 같은 유저를 여러 번 신고한 경우는 1회로 처리한다.
  TEST_F(ReportFixture, 2)
  {
    id_list = {"con", "ryan"};
    report = {"ryan con", "ryan con", "ryan con", "ryan con"};
    k = 3;
    result = {0, 0};

    DoTest();
  }

  TEST_F(ReportFixture, 3)
  {
    id_list = {"a", "b", "c"};
    report = {"a b", "c b"};
    k = 2;
    result = {1, 0, 1};

    DoTest();
  }

  TEST_F(ReportFixture, 4)
  {
    id_list = {"a", "b", "c", "d", "e", "f"};
    report = {"a b", "c b", "d b", "e b", "f b", "a c", "b c"};
    k = 2;
    result = {2, 1, 1, 1, 1, 1};

    DoTest();
  }

  TEST_F(ReportFixture, 5)
  {
    id_list = {"a", "b", "c", "d", "e", "f"};
    report = {"a f", "c f", "d f", "e f", "f b", "a f", "b f"};
    k = 2;
    result = {1, 1, 1, 1, 1, 0};

    DoTest();
  }

  TEST_F(ReportFixture, ReportSizeBoundary)
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