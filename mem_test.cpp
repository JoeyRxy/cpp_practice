#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <concepts>
#include <condition_variable>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <thread>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Point {
    double x = -1, y = -1;
    Point(int x, int y) : x(x), y(y) {
        std::cout << "ctor" << std::endl;
    }
    Point(Point&&p) : x(p.x), y(p.y) {
        std::cout << "move-ctor" << std::endl;
    }
    Point(const Point && p) : x(p.x) , y(p.y) {
        std::cout << "copy-ctor"  << std::endl;
    }
    ~Point() {
        std::cout << "de-ctor" << std::endl;
    }
};

int main(int argc, char const *argv[]) {
    int n = 3;
    {
        allocator<Point> alloc;
        using traits_alloc = allocator_traits<decltype(alloc)>;
        auto p = traits_alloc::allocate(alloc, n);
        for (int i = 0; i < n; ++i) {
            traits_alloc::construct(alloc, p + i, i * 10 + 3, i * 10 + 4);
        }
        for (int i = 0; i < n; ++i) {
            std::cout << p[i].x << ", " << p[i].y << std::endl;
        }
        for (int i = 0 ; i < n; ++i) {
            traits_alloc::destroy(alloc, p + i);
        }
        traits_alloc::deallocate(alloc, p, n);
    }
    {
        auto p = (Point*) malloc(n * sizeof(Point));
        for (int i = 0; i < n; ++i) {
            p[i].x = i * 100 + 3;
            p[i].y = i * 100 + 4;
        }
        for (int i = 0; i < n; ++i) {
            std::cout << p[i].x << ", " << p[i].y << std::endl;
        }
        free(p);
    }
    return 0;
}
