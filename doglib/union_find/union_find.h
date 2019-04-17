#pragma once
#include "../common/range.h"
#include "../common/utils.h"
namespace doglib {
namespace union_find {

struct DoNothing {
    void operator()(int) {}
    void operator()(int, int) {}
    void operator()(int, int, int){};
    void operator()(int, int, int, int) {}
};

template <class Upscaler = DoNothing>
class UnionFind {
    static constexpr bool isTrivial = std::is_same<Upscaler, DoNothing>::value;

  public:
    UnionFind(int N, Upscaler upscaler = DoNothing()) : parent_(N), upscaler(upscaler) {
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
            upscaler(ori_root, x);
        }
        return root;
    }
    int make_root(int node) {
        assert(node < parent_.size());
        static_assert(isTrivial, "NYI");
        int rt = find(node);
        parent_[rt] = node;
        parent_[node] = node;
        return rt;
    }
    bool is_linked(int a, int b) {
        assert(a < parent_.size());
        assert(b < parent_.size());
        int a_r = find(a);
        int b_r = find(b);
        return a_r == b_r;
    }

    template <typename Injector = DoNothing>
    bool merge(int a, int b, Injector injector = DoNothing()) {
        assert(a < parent_.size());
        assert(b < parent_.size());
        static_assert(std::is_same<Injector, DoNothing>::value == isTrivial,
                      "visitor not match");
        int a_r = find(a);
        int b_r = find(b);
        if(a_r == b_r) {
            return false;
        }
        parent_[b_r] = a_r;
        injector(b_r);
        return true;
    }

  private:
    std::vector<int> parent_;
    Upscaler upscaler;
};

}    // namespace union_find
}    // namespace doglib