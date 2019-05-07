#include <gtest/gtest.h>
#include <random>
#include "doglib/common/common.h"
#include "doglib/math/modnum.h"
#include "doglib/math/combination.h"
using namespace doglib::common;
using namespace doglib::math;

// TEST(trivial, naive) {
//     EXPECT_EQ(1, 1);
// }


TEST(combination, advanced) {
    using T = PrimeModNum<100000007>;
    int N = 100000;
    auto comb = &cmb_choose<T>;

    T sum = 0;
    for(int i = 0; i <= N; ++i) {
        sum = sum + comb(N, i);
    }
    T ref = ((T)2).pow(N);
    EXPECT_EQ((ull)sum, (ull)ref);
}
