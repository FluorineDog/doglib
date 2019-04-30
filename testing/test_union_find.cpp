#include <gtest/gtest.h>
#include "doglib/common/common.h"
#include "doglib/common/utils.h"
#include "doglib/union_find/union_find.h"
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
    do{
        iter += 199;
        iter %= N;
        if(iter + 3 < N){
            uf.merge(iter, iter + 3);
        }
    }while(iter != 0);
    for(auto x: Range(N)){
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
    // around 0.592
    EXPECT_LE(ratio, 0.61);
    EXPECT_GT(ratio, 0.57);
}

// TEST(UnionFind, stateful){
//     std::default_random_engine e;
//     std::vector<int> data;
//     constexpr int N = 10000;
//     e.seed(67);

//     for(auto x: Range(N)){
//         data.push_back(e() % 10000);
//     }

//     std::vector<int> mod_data(N, 0);
//     auto scaler = [&](int ori_id, int x_id){
//         mod_data[x_id] += mod_data[ori_id];
//     };

//     UnionFind<decltype(scaler)> uf(N, scaler);

//     e.seed(67);
//     int count = N - 1;
//     do{
        
//         int a = e() % N;
//         int b = e() % N; 
//         if(b == 0){
//             std::swap(a, b);
//         }

//         // int edge = data[b] - data[a];
//         int edge = data[b] - data[a];
//         bool new_connect = uf.merge(a, b, [&](int b_root){
//             mod_data[b_root] = edge - mod_data[b] + mod_data[a];
//         });
        
//         if(new_connect){
//             --count;
//         }
//     }while(count > 0);
//     for(int id: Range(N)){
//         uf.find(id);
//     }
//     int root_v = data[uf.find(0)];
    
//     for(int id: Range(N)){
//         uf.find(id);
//         ASSERT_TRUE(uf.is_linked(0, id));
//         ASSERT_EQ(mod_data[id], data[id]-root_v) << id;
//     }
// }