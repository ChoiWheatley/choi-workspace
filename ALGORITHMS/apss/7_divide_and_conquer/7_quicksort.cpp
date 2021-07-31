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

vector<int>& q_sort(vector<int>& sortee, comparer_t cmp, int begin, int end);
void partition(vector<int>& sortee, int& pivot_idx, comparer_t cmp, int begin, int end);
int my_comparer(const int a, const int b);
void swap(int& a, int& b);
ostream& operator<< (ostream& os, const vector<int>& list);




int main(void)
{
    vector<int> sortee {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    cout << '\n' << q_sort(sortee, my_comparer, 0, sortee.size()) << '\n';
    return 0;
}



// - partition
// - q_sort (left)
// - q_sort (right)
// - return whole sortee
vector<int>& q_sort(vector<int>& sortee, comparer_t cmp, int begin, int end)
{
    if (begin >= end) return sortee;
#   ifdef DBG
    cerr << "\tsortee: " << vector<int>(&sortee[begin], &sortee[end]) << '\n';
#   endif

    int pivot_idx;
    partition(sortee, pivot_idx, cmp, begin, end);
#   ifdef DBG
    cerr << "\tleft: " << vector<int>(&sortee[begin], &sortee[pivot_idx]);
    cerr << "//pivot: " << sortee[pivot_idx];
    cerr << "//right: " << vector<int>(&sortee[pivot_idx+1], &sortee[end]) << '\n';
#   endif
    
    q_sort(sortee, cmp, begin, pivot_idx);                  //left
    q_sort(sortee, cmp, pivot_idx+1, end);    //right

#   ifdef DBG
    cerr << "\tafter sortee: " << sortee << '\n';
#   endif
    return sortee;
}
void partition(vector<int>& sortee, int& pivot_idx, comparer_t cmp, int begin, int end)
{
    int i, j = begin;
    int pivot_item = sortee[begin];
    for (i = begin+1; i < end; i++)
    {
        if (sortee[i] < pivot_item)
        {
            j++;
            swap(sortee[i], sortee[j]);
        }
    }
    pivot_idx = j;
    swap(sortee[j], sortee[begin]);
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
