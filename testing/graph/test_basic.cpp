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


TEST(GraphBasic, naive) {
    EXPECT_EQ(1, 1);
}

TEST(GraphBasic, basic) {
    std::default_random_engine e;
    constexpr int N = 1000;
    DynamicGraph graph(N);
    map<int, vector<int>> ref;
    for(auto i: Range(10 * N)){
        unused(i);
        int from = (int)(e() % N);
        int to = (int)(e() % N);
        graph.add_edge(from, to);
        ref[from].push_back(to);
    }
    for(auto pr: ref){
        auto from = pr.first;
        auto ref_vec = pr.second;
        std::sort(ref_vec.begin(), ref_vec.end());
        vector<int> vec;
        for(auto v: graph.adjacent(from)){
            vec.push_back(v);
        }
        std::sort(vec.begin(), vec.end());
        ASSERT_EQ(vec.size(), ref_vec.size());
        for(auto i: Range(vec.size())){
            ASSERT_EQ(vec[i], ref_vec[i]);
        }
    }
}

TEST(GraphBasic, transpose) {
    std::default_random_engine e;
    constexpr int N = 1000;
    DynamicGraph graph(N);
    map<int, vector<int>> ref;
    for(auto i: Range(10 * N)){
        unused(i);
        int from = (int)(e() % N);
        int to = (int)(e() % N);
        graph.add_edge(from, to);
        ref[to].push_back(from);
    }
    graph = transpose(graph);
    for(auto pr: ref){
        auto from = pr.first;
        auto ref_vec = pr.second;
        std::sort(ref_vec.begin(), ref_vec.end());
        vector<int> vec;
        for(auto v: graph.adjacent(from)){
            vec.push_back(v);
        }
        std::sort(vec.begin(), vec.end());
        ASSERT_EQ(vec.size(), ref_vec.size());
        for(auto i: Range(vec.size())){
            ASSERT_EQ(vec[i], ref_vec[i]);
        }
    }
}
