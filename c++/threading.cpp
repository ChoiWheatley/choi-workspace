#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

int main(int argc, char const *argv[]) {
    thread t([]() {
        for (size_t i = 0; i < 1'000; ++i) {
            cerr << ".";
        }
        cout << "\n";
    });
    // t.detach();
    // t.join();
    this_thread::sleep_for(100ms);
    return 0;
}
