#include <string>
#include <vector>

/**
 * 모든 노드의 자식은 자기보다 항상 작다.
 */
class MaxHeap
{
    std::vector<int> heap;

public:
    MaxHeap &add(int val)
    {
        heap.push_back(val);

        std::size_t pos = heap.size() - 1;
        std::size_t parent_pos = (pos - 1) / 2;
        while (pos > 0 && heap[pos] > heap[parent_pos])
        {
            std::swap(heap[pos], heap[parent_pos]);
            pos = parent_pos;
            parent_pos = (pos - 1) / 2;
        }

        return *(this);
    }

    bool is_empty()
    {
        return heap.empty();
    }

    auto get_max() const -> int
    {
        if (heap.empty())
        {
            return 0;
        }
        return heap.at(0);
    }

    /**
     * 1. root를 제거하고 다음 원소를 올려놓는다.
     * 2. 만약 힙의 속성을 위배한 경우 그 다음 루트의 아래로 sink down 하게 된다.
     */
    auto pop_max() -> int
    {
        if (heap.empty())
        {
            return 0;
        }

        int max = heap[0];

        // pop last object and set to root
        int last = heap.back();
        heap.erase(heap.end() - 1);
        heap[0] = last;

        // sink down last element
        std::size_t child_idx = 0;
        for (std::size_t idx = 0; idx < heap.size(); idx = child_idx)
        {
            child_idx = idx * 2 + 1;
            if (child_idx + 1 < heap.size() && heap.at(child_idx + 1) > heap.at(child_idx))
            {
                child_idx++; // left child VS right child
            }
            if (child_idx < heap.size() && last < heap.at(child_idx))
            {
                std::swap(heap[idx], heap[child_idx]);
            }
            else
            {
                break;
            }
        }

        return max;
    }
};
