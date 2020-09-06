#include <iostream>
#include <string>
using namespace std;

struct Prop
{
    int savings;
    int loan;
};

int CalcProperty(Prop*);

int main(void)
{
    int hong_prop;
    Prop hong = {10000000, 4000000};

    hong_prop = CalcProperty(&hong);

    cout << "재산 : " << hong.savings << " 원에 대출 " << hong.loan
         << "원을 제외한 총 " << hong_prop << "원 입니다." << endl;

    return 0;
}

int CalcProperty(Prop* they)
{
    they->savings *= 2;
    return (they->savings - they->loan);
}