#include "solution.hpp"
#include <gtest/gtest.h>

TEST(BigNumber, Init) {
  auto num = BigNumber("12345");
  ASSERT_EQ("12345", num.to_string());
}
TEST(BigNumber, InitPoint) {
  const string str = "3.141592";
  auto num = BigNumber(str);
  ASSERT_EQ(str, num.to_string());
}
TEST(BigNumber, Multiply) {
  const string a = "3141592";
  const string b = "123";
  const string answer = "386415816";
  auto submit = BigNumber(a) * BigNumber(b);
  ASSERT_EQ(answer, submit.to_string());
}
TEST(BigNumber, Multiply2) {
  const string a = "3.141592";
  const string b = "123";
  const string answer = "386.415816";
  auto submit = BigNumber(a) * BigNumber(b);
  ASSERT_EQ(answer, submit.to_string());
}
TEST(Sol, 1) {
  const string a = "3.141592";
  const size_t exp = 3;
  const string answer = "31.006257328285746688";
  const auto bignum = BigNumber(a);
  auto submit = bignum;
  for (size_t i = 1; i < exp; ++i) {
    submit = submit * bignum;
  }
  ASSERT_EQ(answer, submit.to_string());
}

TEST(Sol, 2) {
  const string a = "1234";
  const size_t exp = 2;
  const string answer = "1522756";
  const auto bignum = BigNumber(a);
  auto submit = bignum;
  for (size_t i = 1; i < exp; ++i) {
    submit = submit * bignum;
  }
  ASSERT_EQ(answer, submit.to_string());
}

TEST(Timeout, 1) {
  const string a = "99.582647139";
  const size_t exp = 100;
  const string answer =
      "658213317897781615229599396569746843688393395170508370248658438110697050"
      "116613435905946499514502950716945516075531983285630183944974254817866781"
      "91135172459952853074590861174747530210281726316819675350."
      "182145119594714267908249189355451088265727872878335146335387396557500554"
      "125597659310408887396455639453591082691073269726291537671903996304568608"
      "197092990684904944230953130137905340201877796355183836346167602688306691"
      "203743261150516696521263352797581976166761060196775003905243352545771690"
      "076644065596095680891136198718852859186308802231056900080578388589600805"
      "832517030108570792742927534573528587193090642746959780202683182688586213"
      "951085644366365379388014461581118614494443806795497668681017702924640354"
      "744142532306148712072404999428602940528707751758051032184272066363811694"
      "550261737586451041747400925078928936405489012347864759536006847617304280"
      "233990809155662420699767554001375100686189272455877885688979261836261847"
      "277683926330187882185282625304428526940955782265338813320064667968174914"
      "132376623001720365996256438572591739842592393377598522261690218763631951"
      "404429541840845237627496813047506001";
  const auto bignum = BigNumber(a);
  auto submit = bignum;
  for (size_t i = 1; i < exp; ++i) {
    submit = submit * bignum;
  }
  ASSERT_EQ(answer, submit.to_string());
}