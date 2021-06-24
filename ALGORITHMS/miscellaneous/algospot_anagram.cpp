/*
	source : https://algospot.com/judge/problem/read/ANAGRAM
문제
Algospot Inc. is planning to launch a new product iWook on September 2011. iWook, is a diskless desktop computer and will be used by geek CS major students around the world. To classify each device, a unique serial number is assigned.

Wookayin, the tech lead of iWook, decided that the password for a iWook device must use all letters from the device’s serial number exactly once in a case-sensitive way, and not in the same order as the original number (*Obviously, in the real world, it’s a faily bad security practice to enforce such restrictions to passwords.*)

Algospot Inc. just hired you to write a program to verify passwords entered by users. For a successful launch, develop the perfect verifier ASAP!

입력
The input consists of T test cases. The number of test cases T is given in the first line of the input.

The following T lines will each contain two strings, the first of which being the serial number of the device, and the second being a password entered by a user for the device.

Both strings will only contain alphanumeric characters, and will not exceed 100 characters in length.

출력
For each test case, print a single line. If the given password is valid for the device, print “Yes” (quotes are for clarity). Otherwise, print “No.”.

예제 입력
3
weird wired
apple angle
apple elppa
예제 출력
Yes
No.
Yes
*/
#include <iostream>
#include <stdlib.h>
#define ASCII_SIZE 128

using namespace std;
bool solve(const string anagram[2]);
void do_count(const string source, char test_case[ASCII_SIZE]);

int main(void)
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		string anagram[2];
		cin >> anagram[0] >> anagram[1];
		cout << (solve(anagram) ? "Yes" : "No.") << "\n";
	}
	return 0;
}
bool solve(const string anagram[2])
{
	if (anagram[0] == anagram[1]) return false;

	char test_case[2][ASCII_SIZE] = {{0}};
	for (int i = 0; i < 2; i++)
	{
		do_count(anagram[i], test_case[i]);
	}

	for (int i = 0; i < ASCII_SIZE; i++)
	{
		if (test_case[0][i] != test_case[1][i])
			return false;
	}
	return true;
}
void do_count(const string source, char test_case[ASCII_SIZE])
{
	for (const char c : source)
	{
		test_case[c]++;
	}
}
