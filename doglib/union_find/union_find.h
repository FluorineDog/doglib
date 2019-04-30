#pragma once
#include "../common/range.h"
#include "../common/utils.h"
namespace doglib {
namespace union_find {
class UnionFind {
  public:
    UnionFind(int N) : parent_(N) {
        for(int i = 0; i < N; ++i) {
            parent_[i] = i;
        }
    }
    int find(int node) {
        assert(node < parent_.size());
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
            int ori_root = parent_[x];
            parent_[x] = root;
        }
        return root;
    }
    bool is_linked(int a, int b) {
        assert(a < parent_.size());
        assert(b < parent_.size());
        int a_r = find(a);
        int b_r = find(b);
        return a_r == b_r;
    }
    int merge(int a, int b) {
        assert(a < parent_.size());
        assert(b < parent_.size());
        int a_r = find(a);
        int b_r = find(b);
        if(a_r != b_r) {
            parent_[b_r] = a_r;
        }
        return a_r;
    }

  private:
    std::vector<int> parent_;
};

}    // namespace union_find
}    // namespace doglib