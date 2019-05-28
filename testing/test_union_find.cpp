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
    for(int i = 0; i < N - 1; ++i) {
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
enum class Grid {
    HorizontalLine,    //
    VerticalLine,
    Block,
    StartNode,
    EndNode,
    CountOfTypes
};

TEST(AdvancedUnionFind, percolation) {
    constexpr int R = 51200;
    constexpr int C = 51200;
    std::default_random_engine e;
    AdvancedUnionFind<Grid> uf({(R + 1) * (C + 1),    //
                                (R + 1) * (C + 1),    //
                                (R + 1) * (C + 1),    //
                                1,                    //
                                1});
    auto get_id = [=](int row, int col) { return row * (C + 1) + col; };
    for(auto i : Range(C)) {
        uf.merge(Grid::HorizontalLine, get_id(0, i), Grid::StartNode, 0);
        uf.merge(Grid::HorizontalLine, get_id(R, i), Grid::EndNode, 0);
    }
    std::vector<bool> grid((R + 1) * (C + 1), false);
    int count = 0;
    while(!uf.is_linked(Grid::StartNode, 0, Grid::EndNode, 0)) {
        int row;
        int col;
        do {
            row = e() % R;
            col = e() % C;
        } while(grid[get_id(row, col)]);
        grid[get_id(row, col)] = true;
        ++count;
        uf.merge(Grid::Block, get_id(row, col), Grid::HorizontalLine, get_id(row, col));
        uf.merge(Grid::Block, get_id(row, col), Grid::HorizontalLine,
                 get_id(row + 1, col));
        uf.merge(Grid::Block, get_id(row, col), Grid::VerticalLine, get_id(row, col));
        uf.merge(Grid::Block, get_id(row, col), Grid::VerticalLine, get_id(row, col + 1));
    }
    double ratio = count * 1.0 / R / C;
    EXPECT_NEAR(ratio, 0.592, 0.02);
}

