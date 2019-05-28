#include <gtest/gtest.h>
#include "doglib/common/common.h"
#include "doglib/common/utils.h"
#include "doglib/union_find/union_find.h"
#include "doglib/union_find/advanced_union_find.h"
#include <random>

// TEST(trivial, naive) {
//     EXPECT_EQ(1, 1);
// }

using namespace doglib;
using namespace doglib::common;
using namespace doglib::union_find;

TEST(UnionFind, mod3) {
    constexpr int N = 1000;
    UnionFind uf(N);
    int iter = 0;
    do {
        iter += 199;
        iter %= N;
        if(iter + 3 < N) {
            uf.merge(iter, iter + 3);
        }
    } while(iter != 0);
    for(auto x : Range(N)) {
        ASSERT_EQ(uf.find(x), x % 3);
    }
}

TEST(UnionFind, percolation) {
    constexpr int N = 512;
    std::default_random_engine e;
    int line = 2 * N + 1;
    UnionFind uf(line * line);
    std::vector<bool> grid(N * N, false);
    int buttom_offset = line * (line - 1);
    for(int i = 0; i < N - 1; ++i){
        uf.merge(2 * i + 1, 2 * i + 3);
        uf.merge(2 * i + 1 + buttom_offset, 2 * i + 3 + buttom_offset);
    }
    int st = 1;
    int ed = st + buttom_offset;
    int count = 0;
    while(!uf.is_linked(st, ed)) {
        int row = e() % N;    
        int col = e() % N;
        int grid_id = row * N + col;
        if(grid[grid_id]) {
            continue;
        }
        grid[grid_id] = true;
        ++count;
        int center = (2 * row + 1) * line + 2 * col + 1;
        uf.merge(center, center + 1);
        uf.merge(center, center - 1);
        uf.merge(center, center + line);
        uf.merge(center, center - line);
    }
    double ratio = (double)count / N / N;
    EXPECT_NEAR(ratio, 0.592, 0.02);
}
enum class Grid{
    HorizontalLine,
    VerticalLine, 
    Block, 
    CountOfTypes
};

TEST(AdvancedUnionFind, percolation) {
    constexpr int R = 512;
    constexpr int C = 512;
    std::default_random_engine e;
    AdvancedUnionFind<Grid> uf({R*C + C, R*C + R, R*C});
   
    // EXPECT_NEAR(ratio, 0.592, 0.02);
}