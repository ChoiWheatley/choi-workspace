#include<iostream>
#include<cmath>
int main(void)
{
	int n, digit = 0, res = 0;
	std::cin >> n;
	for (int i = n; i > 0; i /= 10) digit++;						// to_string(n).size()
	if (digit == 1) res = n;
	else {
		for (int i = 1; i < digit; i++) res += 9*pow(10,i-1)*i;			// digit-1까지
		res += (n+1 - pow(10,digit-1)) * digit;
	}
		std::cout << res << '\n';
	return 0;
}
