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

using namespace std;

class ReadWirteLock{
private:
    mutex read_mtx, write_mtx;
    atomic_int lock_cnt= 0;
public:
    void read_lock() {
        lock_guard<mutex> lk(read_mtx);
        if (++lock_cnt == 1) {
            write_mtx.lock();
        }
    }

    void read_unlock() {
        if (--lock_cnt == 0) {
            write_mtx.unlock();
        }
    }

    void write_lock() {
        write_mtx.lock();
    }

    void write_unlock() {
        write_mtx.unlock();
    }

};

int main(int argc, char const *argv[])
{
    
    return 0;
}

