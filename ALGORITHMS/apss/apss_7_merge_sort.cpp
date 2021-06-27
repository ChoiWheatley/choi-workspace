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
#include <cstdlib>
#include <signal.h>

using namespace std;

vector<int> merge_sort(const vector<int>& sortee);

int main(void)
{
    

    exit(EXIT_SUCCESS);
}
vector<int> merge_sort(const vector<int>& sortee)
{
    if (sortee.size() == 1) return sortee;
    // TODO : 
    // i) 길이 N짜리 수열을 N/2 개 짜리 수열로 쪼갠다.
    // ii) 각 수열에 대한 merge sort 를 재귀적으로 수행한다.
    // iii) 부분수열 두 개를 하나의 수열로 정리하여 리턴한다.
	int size = sortee.size();
    vector<int> split[2];
}
