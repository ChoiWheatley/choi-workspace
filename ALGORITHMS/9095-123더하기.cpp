#include<iostream>
#define MIN_ADD 1
#define MAX_ADD 3
int rec(int remain);
int main(void)
{
	int n, input;
	for (std::cin>>n; n>0; --n){
		std::cin >> input;
		std::cout << rec(input) << '\n';
	}
	return 0;
}
int rec(int remain)
{
	// BASE CONDITION
	if (remain == 0) return 1;
	if (remain < 0)  return 0;

	int cnt = 0;
	for (int i = MIN_ADD; i <= MAX_ADD; i++) {
		remain -= i;
		cnt += rec(remain);
		remain += i;
	}
	return cnt;
}
