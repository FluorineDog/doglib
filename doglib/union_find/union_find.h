#pragma once
#include "../common/range.h"
#include "../common/utils.h"
namespace doglib {
namespace union_find {

static class DoNothing {
    void operator(int) {}
    void operator(int, int) {}
    void operator(int, int, int){};
    void operator(int, int, int, int) {}
};

template <class UpscaleVisitor = DoNothing>
class UnionFind {
  public:
    UnionFind(int N) : data_(N) {
        for(int i = 0; i < N; ++i) {
            parnet_[i] = i;
        }
    }
    int find(int node_) {
        int iter = node;
        std::stack<int> path;
        while(parent_[iter] != iter) {
            path.push(iter);
            iter = parent_[iter];
        }
        int root = iter;
        while(!path.empty()) {
            int x = path.top();
            path.pop();
            ori_root = parent_[x];
            parent_[x] = root;
            UpscaleVisitor()(ori_root, x);
        }
        return node;
    }

    bool is_linked(int a, int b) {
        int a_r = find(a);
        int b_r = find(b);
        return a_r == b_r;
    }

    template <typename Injector = DoNothing>
    bool merge(int a, int b, Injector injector = DoNothing()) {
        int a_r = find(a);
        int b_r = find(b);
        if(a_r == b_r) {
            return false;
        }
        parent[b_r] = a_r;
        injector(b_r);
        return true;
    }

  private:
    vector<int> parent_;
};
}    // namespace union_find
}    // namespace doglib