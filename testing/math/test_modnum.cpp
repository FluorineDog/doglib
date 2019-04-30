#include <gtest/gtest.h>
#include <random>
#include "doglib/common/common.h"
#include "doglib/math/modnum.h"
using namespace doglib::common;
using namespace doglib::math;

TEST(trivial, naive) {
    EXPECT_EQ(1, 1);
}

TEST(modnum, simple) {
    using T = ModNum<1 << 27>;
    T a = 0;
    ull b = 0;
    std::default_random_engine e;
    for(auto idx : Range(10000)) {
        ull rd = e();
        a = a + rd;
        b = b + rd;
        rd = e() | 1;
        a = a * rd;
        b = b * rd;
        rd = e();
        a = rd - a;
        b = rd - b;
        rd = e() % 100000;
        a = a.pow(rd);
        b = std::pow(b, rd);
    }
    EXPECT_EQ((ull)a, b % 64);
}

TEST(modnum, advanced) {
    using T = PrimeModNum<100000007>;
    int N = 1000;
    auto fac = [](int x) {
        T tmp = 1;
        for(auto id : Range(1, x + 1)) {
            tmp = tmp * id;
        }
        return tmp;
    };
    auto comb = [&](int a, int b) {
        return fac(a) / fac(a - b) / fac(b);
    } ;
    T sum = 0;
    for(int i = 0; i <= N; ++i) {
        sum = sum + comb(N, i);
    }
    T ref = ((T)2).pow(N);
    EXPECT_EQ((ull)sum, (ull)ref);
}
