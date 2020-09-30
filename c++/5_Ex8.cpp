/*
 * First input : N, expecting number of input values
 * read the values into a vector
 * then calculate the sum of the N values
 * 
 * Exercise 10 : Modify it to use double instead of int
 * another (N-1) size vector that contains the differencies
 * between adjacent elements
 */

#include "std_lib_facilities.h"
typedef double user_T;

user_T sum (vector<user_T> values);
template <typename T>
void show (vector<T> values);

//
//
int main()
{
	int n = 0;
	cout << "please input the number of the values (N) : \n$\t";
	cin >> n;
	vector<user_T> values(n);
	vector<user_T> diff(n-1);
	for (int i = 0; i < n && cin >> values[i]; i++)
	{
		if (i > 0) { diff[i-1] = abs( values[i-1] - values[i] ); }
	}

	cout << "The sum of " << n << " values : " << sum(values) << endl;
	cout << "The differences of adjacent elements : \n";
	show(diff);

	return 0;
}
//
//

user_T sum(vector<user_T> values)
{
	user_T ret = 0;
	for (auto i : values)
	{
		ret += i;
	}
	return ret;
}
template <typename T>
void show (vector<T> values)
{
	for (auto i : values)
	{
		cout << i << " ";
	}
	cout << '\n';
}