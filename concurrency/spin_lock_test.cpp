#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>
#include <functional>
#include <list>
#include <deque>
#include <queue>
#include <ctime>
#include <random>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <chrono>
#include <regex>
#include <thread>
#include <atomic>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <concepts>
#include <future>
#include <vector>
#include <shared_mutex>

using namespace std;

class SpinLock {
public:
    void lock() {
        bool expect = false;
        while (!_lock.compare_exchange_weak(expect, true)) {
            expect = false;
        }
    }

    void unlock() {
        _lock = false;
    }

    SpinLock() : _lock(false) {}
    
private:
    atomic_bool _lock;
};

SpinLock lk;

void f(int & x) {
    for (int i = 0; i < 100000; ++i) {
        lk.lock();
        ++x;
        lk.unlock();
    }
}

int main(int argc, char const *argv[])
{
    vector<thread> threads;
    int x = 0;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(f, ref(x));
    }
    for (auto& t : threads) {
        t.join();
    }
    std::cout << x << std::endl;
    return 0;
}

