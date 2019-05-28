#pragma once
#include "../common/range.h"
#include "../common/utils.h"
namespace doglib {
namespace union_find {
class UnionFind {
  public:
    explicit UnionFind(int N){
        resize(N);
    }
    void resize(int n){
        int cur_n = static_cast<int>(parent_.size());
        assert(cur_n <= n);
        parent_.reserve(n);
        for(auto idx: common::Range(cur_n, n)) {
            parent_.push_back(idx);
        }
    }
    int find(int node) {
        assert(node < parent_.size());
        int iter = node;
        while(parent_[iter] != iter) {
            iter = parent_[iter];
        }
        int root = iter;
        iter = node;
        while(iter != root) {
            auto ori_rt = parent_[iter];
            parent_[iter] = root;
            iter = ori_rt;
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