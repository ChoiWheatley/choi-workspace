#include <iostream>
using namespace std;

double Add(double, double);
double Sub(double, double);
double Mul(double, double);
double Div(double, double);
double Calc(double, double, double (*)(double, double));

int main(void) {
    double (*calc)(double, double) = NULL;
    double num1 = 3, num2 = 4, result = 0;
    char operand = '/';

    switch (operand) {
        case '+' :
            calc = Add;
            break;
        case '-' :
            calc = Sub;
            break;
        case '*' :
            calc = Mul;
            break;
        case '/' :
            calc = Div;
            break;
        default :
            cout << "사칙연산(+,-,*,/)만 지원합니다." << endl;
            return 1;
    }

    result = Calc(num1, num2, calc);
    cout << "사칙연산의 결과는 " << result << "입니다." << endl;

    return 0;
}

double Add(double x, double y){
    return (x + y);
}
double Sub(double x, double y){
    return (x - y);
}

double Mul(double x, double y){
    return (x * y);
}

double Div(double x, double y){
    return (x / y);
}

double Calc(double x, double y, double (*func)(double, double)){
    return func(x, y);
}
