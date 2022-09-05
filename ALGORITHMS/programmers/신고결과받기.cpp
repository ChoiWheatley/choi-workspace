/// https://school.programmers.co.kr/learn/courses/30/lessons/92334
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
    return (id < other.id);
  }
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
      : Report{.id = id, .to = to}, id_idx{id_idx}, to_idx{to_idx} {}
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
  return Report{.id = words[0], .to = words[1]};
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

static auto CountReports(const set<ReportWithIdx> &reportWithIdx) -> vector<size_t>
{
  auto ret = vector<size_t>(static_cast<int>(reportWithIdx.size()), 0);
  for (auto const &r : reportWithIdx)
  {
    ret.at(r.to_idx) += 1;
  }
  return ret;
}

static auto FindBadUsers(size_t k, const vector<size_t> &countReports) -> set<index_t>
{
  set<index_t> ret;
  for (index_t idx = 0; idx < countReports.size(); ++idx)
  {
    if (k < countReports[idx])
    {
      ret.insert(idx);
    }
  }
  return ret;
}

static vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
  auto answer = vector<int>{static_cast<int>(id_list.size()), 0};

  IndexMap const indexMap = MakeIndexMap(id_list);

  set<Report> const reports = MakeReportSet(report);

  set<ReportWithIdx> const reportWithIdx = MakeReportWithIdx(reports, indexMap);

  vector<size_t> const countReports = CountReports(reportWithIdx);

  set<index_t> const userOverTolerance = FindBadUsers(k, countReports);

  for (auto const &report : reportWithIdx)
  {
    auto const badUser = userOverTolerance.find(report.to_idx);
    if (badUser != userOverTolerance.end())
    {
      answer.at(report.id_idx) += 1;
    }
  }

  return answer;
}

namespace testing
{
  TEST(ParseString, ParseReport)
  {
    auto const str = "muzi frodo";
    auto const ans = Report{"muzi", "frodo"};
    EXPECT_EQ(ans, ParseReport(str));
  }

  TEST(IndexMap, MakeIndexMap)
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

  class ReportFixture : public Test
  {
  protected:
    vector<string> id_list;
    vector<string> report;
    int k;
    vector<int> result;

    auto DoTest() -> void
    {
      ASSERT_GE(id_list.size(), 2);
      ASSERT_LE(id_list.size(), 1000);
      set<string> id_set;
      for (const auto &id : id_list)
      {
        ASSERT_GE(id.size(), 1);
        ASSERT_LE(id.size(), 10);
        // no duplicated elements
        auto [iter, success] = id_set.insert(id);
        ASSERT_TRUE(success);
      }

      ASSERT_GE(report.size(), 1);
      ASSERT_LE(report.size(), 200000);
      for (const auto &each : report)
      {
        ASSERT_GE(each.size(), 3);
        ASSERT_LE(each.size(), 21);
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

      ASSERT_GE(k, 1);
      ASSERT_LE(k, 200);

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

} // namespace testing