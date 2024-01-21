#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class ThreadSafeConfig {
    map<string, int> settings_;
    // mutable keyword: const로 객체가 선언됐을지라도 가변
    mutable shared_mutex rw_;

    void set(const string &name, int value) {
        std::unique_lock lk{rw_};
        settings_.insert_or_assign(name, value);
    }

    int get(const string &name) const {
        std::shared_lock lk{rw_};
        return settings_.at(name);
    }
};

int main(int argc, char const *argv[]) {
    auto thread_safe_config = ThreadSafeConfig{};

    vector<thread> reader_pool{(size_t)10, []() {

                               }};

    return 0;
}
