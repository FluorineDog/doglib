#include <cmath>
#include <gtest/gtest.h>
#include <random>
#include "doglib/common/common.h"
#include "doglib/math/modnum.h"
#include "doglib/math/arithmetic.h"
using namespace doglib::common;
using namespace doglib::math;

// TEST(trivial, naive) {
//     EXPECT_EQ(1, 1);
// }

TEST(modnum, simple) {
    constexpr unsigned mod = 1 << 27;
    using T = ModNum<mod>;
    T a = 0;
    ull b = 0;
    std::default_random_engine e;
    for(auto idx : Range(10000)) {
        (void)idx;
        ull rd = e();
        a += rd;
        b += rd;
        rd = e() | 1;
        a *= rd;
        b *= rd;
        rd = e();
        a = rd - a;
        b = rd - b;
        if(b % 2 == 0) {
            a += 1;
            b += 1;
        }
        rd = e() % 100000;
        a = a.pow(rd);
        b = pow_int(b, rd);
    }
    EXPECT_EQ((ull)a, (unsigned)b % mod);
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
    auto comb = [&](int a, int b) { return fac(a) / fac(a - b) / fac(b); };
    T sum = 0;
    for(int i = 0; i <= N; ++i) {
        sum = sum + comb(N, i);
    }
    T ref = ((T)2).pow(N);
    EXPECT_EQ((ull)sum, (ull)ref);
}
