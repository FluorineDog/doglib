#include <gtest/gtest.h>
#include "doglib/common/common.h"
#include "doglib/common/utils.h"
#include "doglib/common/io.h"
TEST(trivial, naive) {
    EXPECT_EQ(1, 1);
}
using namespace doglib;
using namespace doglib::common;

TEST(DataIter, naive) {
    int sum = 0;
    for(auto iter = make_iter(0); iter < make_iter(100); ++iter) {
        sum += *iter;
    }
    EXPECT_EQ(sum, 4950);
    for(auto x : Range(100)) {
        sum -= x;
    }
    EXPECT_EQ(sum, 0);
}

TEST(DataIter, BinaryFind) {
    int N = 100000;
    auto iter = std::lower_bound(make_iter(0), make_iter(100000), N,
                                 [](int x, int y) { return (long)x * x < y; });
    EXPECT_GE(*iter * *iter, N);
    EXPECT_LT((*iter - 1) * (*iter - 1), N);
}

struct Data{
    int x;
    Data(int x): x(x){}
};

TEST(IO, getter) {
    auto hld = freopen("../../data/io-test.txt", "r", stdin);
    (void)hld;
    auto T = io::get<int>();
    auto N = io::get<int>();
    auto M = io::get<int>();
    auto vec = io::get_vector<int>(M);
    auto vec2 = io::get_vector<Data>(M, [](){
        return Data(100 + io::get<int>());
    });
    ASSERT_EQ(T, 4);
    ASSERT_EQ(N, 3);
    ASSERT_EQ(M, 10);
    for(auto i: Range(M)){
        EXPECT_EQ(vec[i], i + 1);
        EXPECT_EQ(vec2[i].x, i + 101);
        // std::cout << vec2[i].x;
    }
}