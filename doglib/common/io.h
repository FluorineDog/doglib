#pragma once
#include <iostream>
#include "utils.h"
#include "range.h"
namespace doglib {
namespace io {
template <typename T>
T get() {
    T x;
    std::cin >> x;
    return x;
}

template <typename T>
std::vector<T> get_vector(size_t N, T (*getter)(void) = io::get<T>) {
    std::vector<T> tmp;
    tmp.reserve(N);
    using namespace common;
    for(auto _ : Range(N)) {
        tmp.emplace_back(getter());
    }
    return std::move(tmp);
}

}    // namespace io
}    // namespace doglib