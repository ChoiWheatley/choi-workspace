/*
 *  LINK: https://algospot.com/judge/problem/read/QUADTREE
 *  쿼드 트리 만드는 방법은 중요하지 않다. 이번 문제는 쿼드트리를 만드는 것이 아니라
 *  뒤집은 쿼드트리를 만드는 데에 있다.
 *
 *  하나의 이터레이션 안에서의 순서변화는 1,2,3,4 -> 3,4,1,2 순으로 변화한다.
 *  각각의 재귀에 대한 부분까지는 신경쓰지 않아도 된다. 즉, 
 *  x 이후에 뒤따를 4개의 번호의 개수, base condition 따위는 신경쓸 필요가 없다는 의미.
 *
 *
*/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <string>

std::string flipvertical(std::string::iterator & it);

int main(void)
{
    int c;
    std::string each;

    std::cin >> c;
    while (c-->0)
    {
        std::cin >> each;
        auto i = each.begin();
        std::cout << flipvertical(i) << "\n";
    }
    return 0;
}
// x(1234) -> x(3412)
// x(1x....34) -> x(341x....)
std::string flipvertical(std::string::iterator & it)
{
    char c = *it;
    if (c != 'x')
        return std::string{c};
    std::string chunks[4] = {""};
    for (int i = 0; i < 4; i++)
    {
        chunks[i] = flipvertical(++it);
    }
    return 'x' + chunks[2] + chunks[3] + chunks[0] + chunks[1];
}
