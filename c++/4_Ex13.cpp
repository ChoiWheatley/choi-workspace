/*
 * a program that find all the prime number
 * such as 2, 3, 5, 7, 11, ... etc
 * using "Sieve of Eratosthenes"
 */

#include "std_lib_facilities.h"
#include <bitset>

constexpr int bitMax = 999999;

void print (int size, const bitset<bitMax> sieve);
void sievation(int size, bitset<bitMax> & sieve);
vector<int> findPrime(int size, const bitset<bitMax> sieve);

int main()
{
	int max = 0;
	cout << "Please write down your max value(smaller than 999999) : ";
	cin >> max;

	bitset<bitMax> sieve;
	if (max > bitMax)
	{
		cout << "please input smaller value than you wrote." << endl;
		return 1;
	}
	sieve.set();
	sieve.reset(1);
	//print(max, (const bitset<bitMax>){sieve});

	sievation(max, sieve);
	//print(max, (const bitset<bitMax>){sieve});

	
	vector<int> primes;
	primes = findPrime(max, (const bitset<bitMax>){sieve});
	for (int i = 0; i < primes.size(); i++)
	{
		cout << primes[i] << " ";
		if ( !((i+1) % 30) ) cout << endl;
	}
	cout << endl;


	return 0;
}

void print (int size, bitset<bitMax> sieve)
{
	for (int i = size; i > 0; i--)
	{
		cout << sieve[i];
		if (!( (i-1) % 100)) cout << endl;
	}
	cout << endl;
}
void sievation(int size, bitset<bitMax> & sieve)
{
	for (int i = 2; i*i <= size; /*____*/)
	{
		//cout << "i : " << i << endl;
		for (int j = 2; i*j <= size; j++)
			sieve.reset( i*j );		// 0
		// find a least number bigger than the last prime number
		for (int j = i+1; j <= size; j++)
		{
			if (sieve[j])
			{
				i = j;
				break;
			}
		}
		//print(size, (const bitset<bitMax>){sieve});
	}
}

vector<int> findPrime(int size, const bitset<bitMax> sieve)
{
	vector<int> ret;
	for (int i = 1; i <= size; i++)
		if (sieve[i]) ret.push_back(i);
	return ret;
}
