/*
 * A program that performs as a very simple calculator
 * input : two double values and operations (+, -, /, *)
 * output example : "The sum of 35.6 and 24.1 is 59.7"
 */

 #include "std_lib_facilities.h"

double add(double a, double b);
double sub(double a, double b);
double div(double a, double b);
double mul(double a, double b);

int main(void)
{
	cout.precision(15);
	double a, b;
	char op = 0;
	double (*oper) (double, double);

	cout << "Please input two double values and following operator : ";
	while (cin >> a >> b >> op)
	{
		cin.ignore(100, '\n');
		switch (op)
		{
			case '+':
				oper = add;
				break;
			case '-':
				oper = sub;
				break;
			case '/':
				oper = div;
				break;
			case '*':
				oper = mul;
				break;
		}
		cout << "The sum of " <<fixed<< a << " and " <<fixed<< b << " is " <<fixed<< oper(a, b) << endl;
	}
	return 0;
}

double add(double a, double b)
{
	return a + b;
}
double sub(double a, double b)
{
	return a - b;
}
double div(double a, double b)
{
	return a / b;
}
double mul(double a, double b)
{
	return a * b;
}
