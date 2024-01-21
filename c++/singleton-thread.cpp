#include <thread>

inline auto &foo() {
    static int singleton{3};
    return singleton;
}

int main(int argc, char const *argv[]) {
    std::thread t1{foo};
    std::thread t2{foo};

    t1.join();
    t2.join();

    return 0;
}
