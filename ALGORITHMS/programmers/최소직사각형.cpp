// https://school.programmers.co.kr/learn/courses/30/lessons/86491?language=cpp
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <gtest/gtest.h>

using namespace std;

static
vector<int>
fitSizedOf(const vector<int> &cur, const vector<int> &given)
{
    /* cerr << "cur.size = " << cur.size() << "\n"; */
    /* cerr << "given.size = " << given.size() << "\n"; */
    assert(given.size() == cur.size());
    vector<int> ret;
    for (size_t idx = 0; idx < cur.size(); ++idx)
    {
        ret.push_back(
                max(cur[idx], given[idx]));
    }
    return ret;
}

static 
int 
sizeOf(const vector<int> &vec)
{
    int ret = 1;
    for (auto const i : vec)
    {
        ret = ret * i;
    }
    return ret;
}

ostream&
operator<<(ostream& os, const vector<int> &vec)
{
    for (const auto &v : vec)
    {
        os << v << ",";
    }
    os << "\b";
    return os;
}

int solution(vector<vector<int>> sizes) 
{
    int answer = 0;
    auto curRect = vector<int>(size_t(2),int(0));
    for (auto const &c : sizes)
    {
        auto const &orientation1 = c;
        auto const orientation2 = vector<int>{
            c.rbegin(), c.rend()};

        auto const opt1 = fitSizedOf(curRect, orientation1);
        auto const opt2 = fitSizedOf(curRect, orientation2);

        /* cerr << "curRect : " << curRect << "\n"; */
        /* cerr << "[ori1, ori2] : [" << orientation1 << "," << orientation2 << "]\n"; */
        /* cerr << "[opt1, opt2] : [" << opt1 << "," << opt2 << "]\n"; */

        if (sizeOf(opt1) < sizeOf(opt2))
        {
            curRect = std::move(opt1);
        } 
        else 
        {
            curRect = std::move(opt2);
        }

        int mult = 1;
        for (auto const &i : curRect)
        {
            mult = mult * i;
        }
        answer = mult;
    }
    return answer;
}

TEST(TestCase, 1)
{
    auto const sizes = vector<vector<int>>{
        {60, 50},
        {30, 70},
        {60, 30},
        {80, 40},
    };
    auto const answer = 4000;
    EXPECT_EQ(answer, solution(sizes));
}

TEST(TestCase, 2)
{
    auto const sizes = vector<vector<int>>{
        {10,7},
        {12,3},
        {8,15},
        {14,7},
        {5,15},
    };
    auto const answer = 120;
    EXPECT_EQ(answer, solution(sizes));
}

TEST(TestCase, 3)
{
    auto const sizes = vector<vector<int>>{
        {14,4},
        {19,6},
        {6,16},
        {18,7},
        {7,11},
    };
    auto const answer = 133;
    EXPECT_EQ(answer, solution(sizes));
}
