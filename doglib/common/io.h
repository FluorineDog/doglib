#pragma once
#include <iostream>
#include <tuple>
#include "utils.h"
#include "range.h"
namespace doglib {
namespace io {
template <typename T = int>
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
    for(auto x : Range(N)) {
        (void)x;
        tmp.emplace_back(getter());
    }
    return std::move(tmp);
}

void set_cin_source(std::string path, int argc = 0, char* argv[] = NULL) {
    (void)path;
#ifndef DOG_DEBUG
    return;
#endif
    if(argc == 2) {
        freopen(argv[1], "r", stdin);
    } else {
        freopen(path.c_str(), "r", stdin);
    }
}

}    // namespace io
}    // namespace doglib

template <typename T, typename U>
std::istream& operator>>(std::istream& in, std::pair<T, U>& pr) {
    using namespace doglib;
    pr.first = io::get<T>();
    pr.second = io::get<U>();
    return in;
}