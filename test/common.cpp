#include <gtest/gtest.h>
#include "doglib/common/common.h"
TEST(trivial, naive){
    EXPECT_EQ(1, 1);
}
using namespace doglib::common;

TEST(Common, DataIter){
    int sum = 0;
    for(auto iter = make_iter(0); iter < make_iter(100); ++iter){
        sum += *iter;
    }
    EXPECT_EQ(sum, 4950);
}


