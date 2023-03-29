#include <cassert>
#include <string>
using namespace std;
const string STR1 = "hello1";
const string STR2 = "hello2";
struct Test {
  string s;
  string *s_p;
  explicit Test(const string &s) : s{s}, s_p{&this->s} {}
};
int main(void) {
  Test test1(STR1);
  Test test2(STR2);
  std::swap(test1, test2);
  assert(STR2 == *test2.s_p);
  assert(STR1 == *test1.s_p);
}