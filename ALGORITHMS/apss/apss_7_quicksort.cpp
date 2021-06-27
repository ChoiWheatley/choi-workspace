/*
 * 병합정렬과 비슷하지만 병합 과정을 없앤 정렬 방식을 '퀵소트' 라고 부른다.
 * 퀵소트는 임의의 피벗을 기준으로 작은 값은 왼쪽 수열로, 큰 값은 오른쪽 
 * 수열로 옮기게 된다. 이를 '파티션' 과정이라고 부른다. 분할이 완료된 
 * 두 수열을 단순히 피벗 양쪽으로 붙이면 끝나게 된다.
 * 
 * 퀵소트는 피벗의 위치에 따라 시간복잡도가 갈리게 되는데, 만일 피벗이 수열의
 * 가장 작은 값이나 가장 큰 값으로 설정된다면 부분문제의 크기가 하나씩밖에
 * 줄어들 수 없게 된다. 이때의 시간복잡도는 O(N**2) 가 된다.
 * 피벗이 병합정렬처럼 매 순간 수열의 중간값을 가리킨다면 시간복잡도는 O(nlgn)
 * 이 된다고 한다.
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <unistd.h>
#include <utility>

using namespace std;
typedef int (*comparer_t)(const int, const int);

vector<int> q_sort(vector<int>& sortee, comparer_t cmp);
void partition(vector<int>& sortee, int& pivot_idx, comparer_t cmp);
int my_comparer(const int a, const int b);
void swap(int& a, int& b);
ostream& operator<< (ostream& os, const vector<int>& list);

int main(void)
{
    vector<int> sortee {5,4,3,2,1};
    cout << '\n' << q_sort(sortee, my_comparer) << '\n';
    return 0;
}
vector<int> q_sort(vector<int>& sortee, comparer_t cmp)
{
    if (sortee.size() == 1) return sortee;
#ifdef DBG
    cerr << "\tsortee=" << sortee << '\n';
#endif
    
    int pivot_idx;
    partition(sortee, pivot_idx, cmp);

    vector<int> left{ &sortee[0], &sortee[pivot_idx] };
    vector<int> right{ &sortee[pivot_idx], &sortee[sortee.size()] };

#ifdef DBG
    cerr << "\tleft=" << left << "\n\tright=" << right << '\n';
#endif
    q_sort(left, cmp);
    q_sort(right, cmp);

    move( left.begin(), left.end(), back_inserter(right) );
#ifdef DBG
    cerr << "\tafter sortee=" << sortee << '\n';
#endif
   
    return left;
}
void partition(vector<int>& sortee, int& pivot_idx, comparer_t cmp)
{
    int i, j = 0;
    int pivot_item = sortee[0];

    for (i = 1; i < sortee.size(); i++)
    {
        if (cmp(sortee[i], pivot_item) < 0)
        {
            j++;
            swap(sortee[i], sortee[j]);
        }
    }
    pivot_idx = j;
    swap(sortee[j], sortee[0]);
}
int my_comparer(const int a, const int b)
{
    return a - b;
}
void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
ostream& operator<< (ostream& os, const vector<int>& list)
{
	os << "{ ";
    if (list.empty())
        os << "empty  ";
	for (auto i : list)
	{
		os << i << ", ";
	}
	os << "\b\b }";
	return os;
}
