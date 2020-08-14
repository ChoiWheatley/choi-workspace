#include <iostream>
using namespace std;

double Add (double, double);
double Sub (double, double);
double Mul (double, double);
double Div (double, double);
double Cal (double, double, double (*func)(double, double));


int main() {
    double (*calc)(double, double) = NULL;
    double num1, num2;
    char operand = 0;
    cout << "피연산자 두개를 입력하시오 {a b} : ";
    cin >> num1 >> num2;
    cout << "연산자를 입력하시오 {-, +, /, *} : ";
    cin >> operand;

    switch (operand) {
        case '-' :
            calc = Sub;
            break;
        case '+' :
            calc = Add;
            break;
        case '/' :
            calc = Div;
            break;
        case '*' :
            calc = Mul;
            break;
    }

    cout << Cal(num1, num2, calc) << endl;

    return 0;
}

double Add (double a, double b){ return a + b; }
double Sub (double a, double b){ return a - b;}
double Mul (double a, double b){ return a * b;}
double Div (double a, double b){ return a / b;}
double Cal (double a, double b, double (*func)(double, double)) { return func(a, b); }