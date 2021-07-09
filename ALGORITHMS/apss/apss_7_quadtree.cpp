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

std::string flipvertical(const std::string& origin);

int main(void)
{
    int c;
    std::string each;

    std::cin >> c;
    while (c-->0)
    {
        std::cin >> each;
        std::cout << flipvertical(each) << "\n\n";
    }
    return 0;
}
// x(1234) -> x(3412)
// x(1x....34) -> x(341x....)
std::string flipvertical(const std::string& origin)
{
    if (origin.size() == 1) 
        return origin;
    if (origin[0] != 'x')
        return std::to_string(origin[0]);
    std::cerr << origin << '\n';


    // 4 개의 덩어리만 본다. 중간에 x 가 끼어있으면 
    // 남은 덩어리 수의 개수만 제외하고 몽땅 다음 
    // 이터레이션으로 넘겨버린다.
    std::string chunk[4] = {""};
    int count_index = 0;
    for (int i = 1; i < origin.size(); i++)
    {
        if (origin[i] == 'x')
        {
            chunk[count_index] = flipvertical ( 
                std::string {origin.begin()+i, origin.end()-(3-count_index)} 
            );
            i = origin.size()-(3-count_index);
            count_index++;
            continue;
        }
        chunk[count_index++] = origin[i];
    }
    
    std::string ret;
    ret += 'x' + chunk[2] + chunk[3] + chunk[0] + chunk[1];
    return ret;
}
