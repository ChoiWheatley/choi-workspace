/*
첫순열 : 비내림차순 (1,2,3,4)
마지막순열 : 비오름차순 (4,3,2,1)
다음순열 : 무엇으로 시작하는 어떤 순열이 마지막 순열이라면 그 다음 순열은 한 자리수가 올라간 첫 순열이 된다.

1. A[i-1] > A[i] 인 가장 큰 i 를 구한다
2. [i,A.size()) 구간에서 A[i-1] 보다 작은 가장 큰 원소의 인덱스를 j로 둔다
3. swap(A[i-1], A[j])
4. [i,A.size()) 구간을 뒤집어 첫순열로 만들어준다.

[ 7 2 3 6 5 4 1 ].next_permu() 
   > < < > > >
        ^------------- i ( 어떤 순열의 i번째부터 비오름차순이므로 곧 마지막 순열을 의미한다.)         
		    ^--------- j ( [i-1] 보다는 크고 해당 마지막 순열의 원소 중 가장 작은 원소를 의미)
swap ([i-1], [j])
[ 7 2 4 6 5 3 1 ] (아직 안 끝났어)
        ^^^^^^^------- 첫순열로 만들어주기 위해 뒤집어준다.
[ 7 2 4 1 3 5 6 ]
*/
#include<iostream>
#include<vector>

// return value : is this sequence 'not' a last sequence?
bool next_permutation(std::vector<int>& sequence);
void swap(int& a, int& b);

int main(void)
{
	std::vector<int> seq;
	int input = 0;
	for (;std::cin >> input;){
		seq.push_back(input);
	}
	for(auto i : seq) std::cout << i << ' ';
	for (;next_permutation(seq);){
		std::cout << '\n';
		for(auto i : seq) std::cout << i << ' ';
	}
	std::cout << '\n';
	return 0;
}
// return value : is this sequence 'not' a last sequence?
bool next_permutation(std::vector<int>& sequence)
{
	int i = 0, j = 0;
	for (i = sequence.size()-1; i >= 0; i--){
		if (i == 0) return false;		// 전체순열의 마지막 번째
		if (sequence[i-1] < sequence[i]) break;
	}
	// 내림차순의 순열에서 바꿀 수보다 작다는 건 곧 그 이전수가 된다.
	for (j = i; j < sequence.size()-1; j++)
		if (sequence[j+1] < sequence[i-1]) break;
	swap(sequence[i-1], sequence[j]);
	for (int k = sequence.size()-1; k > i; k--)
		swap(sequence[i++], sequence[k]);
	return true;
}
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
