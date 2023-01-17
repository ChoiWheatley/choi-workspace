#include "solution.hpp"
#include <iostream>

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;
    MaxHeap heap{};
    while (n-- > 0)
    {
        int val;
        std::cin >> val;
        if (val == 0)
        {
            std::cout << heap.pop_max() << "\n";
        }
        heap.add(val);
    }
}