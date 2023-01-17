#include <vector>

/**
 * 모든 노드의 자식은 자기보다 항상 작다.
 */
class MaxHeap
{
    const int N;
    std::vector<int> heap;

public:
    explicit MaxHeap(int n = 100) : N{n * 2}, heap{n}
    {
    }

    void add(int val)
    {
        heap.push_back(val);

        size_t pos = heap.size() - 1;
        size_t parent_pos = pos / 2;
        while (pos > 0 && heap.at(parent_pos) < val)
        {
            std::swap(heap[pos], heap[parent_pos]);
            pos = parent_pos;
            parent_pos /= 2;
        }
    }

    auto get_max() -> int
    {
        if (heap.empty())
        {
            return 0;
        }
        return heap.at(0);
    }
};