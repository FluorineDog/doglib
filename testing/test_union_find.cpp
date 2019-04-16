#include <gtest/gtest.h>
#include "doglib/common/common.h"
#include "doglib/common/utils.h"
#include "doglib/union_find/union_find.h"
#include <random>

TEST(trivial, naive) {
    EXPECT_EQ(1, 1);
}
using namespace doglib;
using namespace doglib::common;
using namespace doglib::union_find;

// TEST(UnionFind, mod3) {
//     constexpr int N = 1000;
//     UnionFind uf(N);
//     int iter = 0;
//     do{
//         if(iter + 3 >= N){
//             continue;
//         }
//         uf.merge(iter, iter + 3);
//         iter += 199;
//         iter %= N;
//     }while(iter != 0);
//     for(auto x: Range(N)){
//         ASSERT_EQ(uf.find(x), x % 3);
//     }
// }

// TEST(UnionFind, fuck3){
//     std::default_random_engine e;
//     std::vector<int> data;
//     constexpr int N = 1000;
//     e.seed(67);

//     for(auto x: Range(N)){
//         data.push_back(e() % 10);
//     }

//     std::vector<int> mod_data(N, 0);
//     auto scaler = [&](int ori_id, int x_id){
//         mod_data[x_id] += mod_data[ori_id];
//         mod_data[x_id] %= 10;
//     };

//     UnionFind<decltype(scaler)> uf(N);

//     e.seed(67);
//     int count = N;
//     do{
        
//         int i = e() % N;
//         int j = e() % N; 
//         int edge = data[j] - data[i];
//         edge = edge >= 0? edge : edge + 10;

//         // bool new_connect = uf.merge()
//         // if(new_connect){
//         //     --count;
//         // }
//     }while(count);
    
//     auto scaler = []()
// }