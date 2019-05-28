#include "union_find.h"
namespace doglib {
namespace union_find {
template <typename EnumType>
class AdvancedUnionFind {
  public:
    explicit AdvancedUnionFind(std::vector<int> limits):uf_(0) {
        int sum = 0;
        offsets_.push_back(sum);
        for(auto x : limits) {
            sum += x;
            offsets_.push_back(sum);
        }
        uf_.resize(sum);
        limits_ = limits;
    }
    int find(EnumType node_type, int node_id){
        return uf_.find(to_uid(node_type, node_id));
    }

    bool is_linked(EnumType a_type, int a_id, EnumType b_type, int b_id){
        auto a = to_uid(a_type, a_id);
        auto b = to_uid(b_type, b_id);
        return uf_.is_linked(a, b);
    }
    
    bool merge(EnumType a_type, int a_id, EnumType b_type, int b_id) {
        auto a = to_uid(a_type, a_id);
        auto b = to_uid(b_type, b_id);
        return uf_.merge(a, b);
    }
  private:
    int to_uid(EnumType type, int idx){
        int type_id = static_cast<int>(type);
        assert(idx < limits_[type_id]);
        return offsets_[type_id] + idx;
    }
    UnionFind uf_;
    std::vector<int> offsets_;
    std::vector<int> limits_;
};
}    // namespace union_find
}    // namespace doglib
