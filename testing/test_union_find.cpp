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

TEST(UnionFind, mod3) {
    constexpr int N = 1000;
    UnionFind<> uf(N);
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

TEST(UnionFind, fuck3){
    std::default_random_engine e;
    std::vector<int> data;
    constexpr int N = 1000;
    e.seed(67);

    for(auto x: Range(N)){
        data.push_back(e() % 10);
    }

    std::vector<int> mod_data(N, 0);
    auto scaler = [&](int ori_id, int x_id){
        mod_data[x_id] += mod_data[ori_id];
        mod_data[x_id] %= 10;
    };

    UnionFind<decltype(scaler)> uf(N, scaler);

    e.seed(67);
    int count = N - 1;
    do{
        
        int a = e() % N;
        int b = e() % N; 
        if(a > b){
            std::swap(a, b);
        }
        int edge = data[b] - data[a];

        bool new_connect = uf.merge(a, b, [&](int b_root){
            mod_data[b_root] = (edge - mod_data[b] + mod_data[a] + 20) % 10;
        });
        
        if(new_connect){
            --count;
        }
    }while(count > 0);
    for(int id: Range(N)){
        uf.find(id);
        ASSERT_TRUE(uf.is_linked(0, id));
        ASSERT_EQ(mod_data[id], id % 10) << id;
    }
}