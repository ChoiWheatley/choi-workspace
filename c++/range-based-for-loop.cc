#include <iostream>

/**
 * @brief 커스텀 컨테이너, 근데 RBFL를 가능하게 만든.
 *
 */
class MyContainer {
    int *mArr;
    size_t mSize;

  public:
    class iterator {
        int *mCur;

      public:
        explicit iterator(int *position) : mCur{position} {}

        /// @brief 전위 증가연산자
        iterator &operator++() {
            mCur++;
            return *this;
        }

        /// @brief end 여부와 비교하기 위한 연산자
        friend bool operator!=(const iterator &lhs, const iterator &rhs) {
            return lhs.mCur != rhs.mCur;
        }

        int &operator*() { return *mCur; }
    };
    MyContainer(size_t size) : mArr{new int[size]}, mSize{size} {}

    iterator begin() { return iterator{mArr}; }
    iterator end() { return iterator{mArr + mSize}; }

    int &operator[](size_t idx) { return mArr[idx]; }
};

int main(void) {
    std::cout
        << R"(1. 아래는 정적크기 배열을 RBFL(range-based-for-loop)에 넣었을 때
    정상작동하는 모습을 보여준다.
)";
    int array[] = {1, 2, 3, 4, 5};
    for (auto i : array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout
        << R"(2. 아래는 커스텀 컨테이너 MyContainer를 만들어서 RBFL을 돌렸을 때
    정상작동하는 모습을 보여준다.
)";
    MyContainer container{5};
    for (size_t i = 0; i < 5; ++i) {
        container[i] = i * i;
    }
    for (auto itr = container.begin(); itr != container.end(); ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    for (auto i : container) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
