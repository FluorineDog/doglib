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
    // std::shuffle(mp.begin(), mp.end(), e);
    DynamicGraph graph(N);
    for(auto ig : Range(N * 100)) {
        unused(ig);
        int from = (int)(e() % (N - 1));
        int to = (int)(e() % (N - 1 - from)) + from + 1;
        assert(from < to);
        graph.add_edge(mp[from], mp[to]);
    }
    for(auto ig : Range(N - 1)) {
        int from = mp[ig];
        int to = mp[ig + 1];
        assert(from < to);
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
}
