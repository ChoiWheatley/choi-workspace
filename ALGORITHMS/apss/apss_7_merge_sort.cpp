/*
    AUTHOR : Choi Wheatley (chltmdgus604@naver.com)
    BREIF : implementing merge sort
    병합정렬은 분할정복의 아주 훌륭한 예시이다. 매 수열을 반씩 갈라 
    길이 1인 수열을 N개 만든 다음 하나씩 병합해 가면서 정렬을 수행
    하는 방식이다. 시간복잡도는 길이1인 수열을 만드는데 lg(N),
    각 단계에서 병합을 수행하는데 (N) 복잡도가 걸린다. 따라서 lg(N)
    개의 단계를 병합을 수행하기 위해선 Nlg(N)이 된다. 
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>

using namespace std;
typedef int (*compare_t)(const int, const int);

vector<int> merge_sort(const vector<int>& sortee, compare_t cmp);
int compare (const int a, const int b);
ostream& operator<< (ostream& os, const vector<int>& list);

int main(void)
{
    vector<int> sortee {100,99,98,6,5,4,3,2,10,11,12,13,14,9,8,7,90,91,92,93,94,95,96,97};
    vector<int> ret = merge_sort(sortee, compare);
	cout << '\n' << ret << '\n';
    exit(EXIT_SUCCESS);
}
vector<int> merge_sort(const vector<int>& sortee, compare_t cmp)
{
    if (sortee.size() == 1) return sortee;
    // TODO : 
    // i) 길이 N짜리 수열을 N/2 개 짜리 수열로 쪼갠다.
    // ii) 각 수열에 대한 merge sort 를 재귀적으로 수행한다.
    // iii) 부분수열 두 개를 하나의 수열로 정리하여 리턴한다.
	int size = sortee.size();
    vector<int> ret;
    vector<int> split[2] = { 
        vector<int>(&sortee[0], &sortee[size/2]), 
        vector<int>(&sortee[size/2], &sortee[size]) 
    };

	cerr << split[0] << ", " << split[1] << " --> ";
    for (int i = 0; i < 2; i++)
        split[i] = merge_sort(split[i], cmp);
	cerr << split[0] << ", " << split[1] << '\n';
	
    // 이제 split[0], [1]은 각각 정렬이 완성됐다고 볼 수 있다.
    // 두 벡터의 앞에서부터 차례차례 삽입하면 된다.
    vector<int>::iterator it0 {split[0].begin()};
    vector<int>::iterator it1 {split[1].begin()};
	while(true)
    {
#		ifdef DBG
		cerr << *it0 << "," << *it1 << '\t';
#		endif
		if (it0 == split[0].end() && it1 == split[1].end())
			break;
		if (it0 == split[0].end()) {
			ret.push_back(*it1++);
		} else if (it1 == split[1].end()) {
			ret.push_back(*it0++);
		} else if (cmp(*it0, *it1) < 0) {
			ret.push_back(*it0++);
		} else {
			ret.push_back(*it1++);
		}
	}
	cerr << '\n';

    return ret;
}
int compare (const int a, const int b)
{
	return a - b;
}
ostream& operator<< (ostream& os, const vector<int>& list)
{
	os << "{ ";
	for (auto i : list)
	{
		os << i << ", ";
	}
	os << "\b\b }";
	return os;
}
