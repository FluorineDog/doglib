#include <gtest/gtest.h>
#include "doglib/common/common.h"
#include "doglib/common/utils.h"
TEST(trivial, naive){
    EXPECT_EQ(1, 1);
}
using namespace doglib::common;

TEST(DataIter, naive){
    int sum = 0;
    for(auto iter = make_iter(0); iter < make_iter(100); ++iter){
        sum += *iter;
    }
    EXPECT_EQ(sum, 4950);
    for(auto x: Range(100)){
        sum -= x;
    }
    EXPECT_EQ(sum, 0);
}

TEST(DataIter, BinaryFind){
    int N = 100000;
    auto iter = std::lower_bound(make_iter(0), make_iter(100000), N, [](int x, int y){
        return (long)x*x < y;
    });
    EXPECT_GE(*iter * *iter, N);
    EXPECT_LT((*iter - 1) * (*iter - 1), N);
    
}
