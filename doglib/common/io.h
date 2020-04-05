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

template <typename T, typename Func=T(void)>
std::vector<T> get_vector(size_t N, Func getter = io::get<T>) {
    std::vector<T> tmp;
    tmp.reserve(N);
    using namespace common;
    for(auto x : Range(N)) {
        (void)x;
        tmp.emplace_back(getter());
    }
    return tmp;
}

inline void set_cin_source(std::string path, int argc = 0, char* argv[] = NULL) {
#ifdef DOG_DEBUG
    if(argc == 2) {
        freopen(argv[1], "r", stdin);
    } else {
        freopen(path.c_str(), "r", stdin);
    }
#else
    (void)path;
    (void)argc;
    (void)argv;
#endif
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
template <typename T0, typename T1, typename T2>
std::istream& operator>>(std::istream& in, std::tuple<T0, T1, T2>& tp) {
    using namespace doglib;
    std::get<0>(tp) = io::get<T0>();
    std::get<1>(tp) = io::get<T1>();
    std::get<2>(tp) = io::get<T2>();
    return in;
}