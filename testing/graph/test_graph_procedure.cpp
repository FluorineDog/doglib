#include <gtest/gtest.h>
#include "doglib/common/common.h"
#include "doglib/common/utils.h"
#include "doglib/graph/graph.h"
#include "doglib/graph/procedure.h"
#include <random>
using namespace doglib;
using namespace doglib::common;
using namespace doglib::graph;
using namespace std;

TEST(GraphProcedure, naive) {
    EXPECT_EQ(1, 1);
}

#define ASSERT_VEC_EQ(vec1, vec2)            \
    do {                                     \
        ASSERT_EQ(vec1.size(), vec2.size()); \
        for(auto i : Range(vec1.size())) {   \
            ASSERT_EQ(vec1[i], vec2[i]);     \
        }                                    \
    } while(false)

TEST(GraphProcedure, dfs) {
    vector<int> mp;
    default_random_engine e;
    constexpr int N = 1000;
    for(auto i : Range(N)) {
        mp.push_back(i);
    }
    std::shuffle(mp.begin(), mp.end(), e);
    DynamicGraph graph(N);
    for(auto ig : Range(N - 1)) {
        int from = mp[ig];
        int to = mp[ig + 1];
        graph.add_edge(from, to);
    }
    vector<int> discover_vec;
    vector<int> finish_vec;
    int last_discover = -1;
    bool succ = true;
    ProcedureDFS dfs(graph);
    dfs.set_visitor(Transfer::discover, [&](int u, int v) {
        succ = succ && last_discover == u;
        last_discover = v;
        discover_vec.push_back(v);
    });
    dfs.set_visitor(Transfer::finish, [&](int, int v) { finish_vec.push_back(v); });
    dfs.execute_at(mp[0]);
    ASSERT_TRUE(succ);
    ASSERT_VEC_EQ(discover_vec, mp);
    std::reverse(finish_vec.begin(), finish_vec.end());
    ASSERT_VEC_EQ(finish_vec, mp);
}

TEST(GraphProcedure, acycle) {
    vector<int> mp;
    default_random_engine e;
    constexpr int N = 1000;
    for(auto i : Range(N)) {
        mp.push_back(i);
    }
    std::shuffle(mp.begin(), mp.end(), e);
    DynamicGraph graph(N);
    for(auto ig : Range(N * 10)) {
        unused(ig);
        int from = (int)(e() % (N - 1));
        int to = (int)(e() % (N - 1 - from)) + from + 1;
        assert(from < to);
        graph.add_edge(mp[from], mp[to]);
    }
    for(auto ig : Range(N - 1)) {
        int from = mp[ig];
        int to = mp[ig + 1];
        graph.add_edge(from, to);
    }
    for(auto ig : Range(N * 10)) {
        unused(ig);
        int from = (int)(e() % (N - 1));
        int to = (int)(e() % (N - 1 - from)) + from + 1;
        assert(from < to);
        graph.add_edge(mp[from], mp[to]);
    }
    auto order = toposort_acycle(graph);
    ASSERT_VEC_EQ(order, mp);
    graph.add_edge(mp[100], mp[10]);
    order = toposort_acycle(graph);
    ASSERT_EQ(order.size(), 0);
}

TEST(GraphProcedure, cycle) {
    vector<int> mp;
    default_random_engine e;
    constexpr int N = 1000;
    constexpr int K = 5;
    for(auto i : Range(N * K)) {
        mp.push_back(i);
    }
    std::shuffle(mp.begin(), mp.end(), e);
    vector<int> remp(N * K);
    for(auto i : Range(N * K)) {
        remp[mp[i]] = i;
    }
    DynamicGraph graph(N * K);
    for(auto ig : Range(N * 10)) {
        unused(ig);
        int from = (int)(e() % (N));
        int to = (int)(e() % (N - from)) + from;
        auto a = mp[from * K + e() % K];
        auto b = mp[to * K + e() % K];
        graph.add_edge(a, b);
    }
    for(auto ig : Range(N - 1)) {
        int from = ig;
        int to = ig + 1;
        int k1 = (int)(e() % K);
        int k2 = (int)(e() % K);
        auto a = mp[from * K + k1];
        auto b = mp[to * K + k2];
        graph.add_edge(a, b);
    }
    for(auto ig : Range(N)) {
        for(auto k : Range(K)) {
            int from = ig;
            int to = ig;
            int k1 = k;
            int k2 = (k + 1) % K;
            auto a = mp[from * K + k1];
            auto b = mp[to * K + k2];
            graph.add_edge(a, b);
        }
    }
    auto order = toposort_cycle(graph);
    for(auto i : Range(N * K)) {
        EXPECT_EQ(remp[order[i]] / K, i / K);
    }
}

TEST(GraphProcedure, scc) {
    vector<int> mp;
    default_random_engine e;
    constexpr int N = 1000;
    constexpr int K = 5;
    for(auto i : Range(N * K)) {
        mp.push_back(i);
    }
    std::shuffle(mp.begin(), mp.end(), e);
    vector<int> remp(N * K);
    for(auto i : Range(N * K)) {
        remp[mp[i]] = i;
    }
    DynamicGraph graph(N * K);
    for(auto ig : Range(N * 10)) {
        unused(ig);
        int from = (int)(e() % (N));
        int to = (int)(e() % (N - from)) + from;
        auto a = mp[from * K + e() % K];
        auto b = mp[to * K + e() % K];
        graph.add_edge(a, b);
    }
    for(auto ig : Range(N - 1)) {
        int from = ig;
        int to = ig + 1;
        int k1 = (int)(e() % K);
        int k2 = (int)(e() % K);
        auto a = mp[from * K + k1];
        auto b = mp[to * K + k2];
        graph.add_edge(a, b);
    }
    for(auto ig : Range(N)) {
        for(auto k : Range(K)) {
            int from = ig;
            int to = ig;
            int k1 = k;
            int k2 = (k + 1) % K;
            auto a = mp[from * K + k1];
            auto b = mp[to * K + k2];
            graph.add_edge(a, b);
        }
    }
    auto pr = construct_scc(graph);
    auto order = pr.first;
    for(auto i : Range(N)) {
        EXPECT_EQ(order[mp[i]], i / K);
    }
}