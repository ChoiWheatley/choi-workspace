/*
 * convert a digit into its corresponding spelled-out value
 * 
 * input : 7245
 * output : seven two four five
 */

#include "std_lib_facilities.h"

const vector<string> digits = 
{
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

int main(void)
{
	string number = "";
	while (cin >> number)
	{
		cin.ignore(100, '\n');
		for (int i = 0; i < number.size(); i++)
		{
			string spell = digits [   int{number[i]}-48   ];
			cout << spell << " ";
			//cout << int{number[i]} - 48 << " ";
		}
		cout << endl;
	}

	return 0;
}
