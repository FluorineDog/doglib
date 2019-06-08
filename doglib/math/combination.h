#pragma once
#include <vector>
#include "../common/common.h"
using namespace doglib::common;

namespace doglib {
namespace math {
using ull = long long;
template <typename T>
auto factorial(int x) -> T {
    thread_local std::vector<T> memory(1, (T)1);
    assert(x >= 0);
    if(x + 1 >= memory.size()) {
        memory.reserve(2 * x + 10);
        T last = memory.back();
        for(auto idx : Range((int)memory.size(), 2 * x + 10)) {
            last = last * idx;
            memory.emplace_back(last);
        }
    }
    return memory[x];
}

template <typename T>
auto cmb_choose(int b, int a) -> T{
    return factorial<T>(b) / factorial<T>(b - a) / factorial<T>(a);
}

template <typename T>
auto cmb_permute(int b, int a) -> T {
    return factorial<T>(a) / factorial<T>(a);
}

}    // namespace math
}    // namespace doglib
