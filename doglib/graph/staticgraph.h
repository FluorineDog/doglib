#include "graph.h"
namespace doglib{
namespace graph{
class StaticGraph {
  private:
    std::vector<int> vertex_begs_;
    std::vector<int> edges_;    // 2 only
    friend class DynamicGraph;

  public:
    StaticGraph() = default;
    explicit StaticGraph(const DynamicGraph& dyn_graph) {
        int n_vertex = dyn_graph.n_vertex();
        vertex_begs_.push_back(0);
        for(int v = 0; v < n_vertex; ++v) {
            for(auto v_adj : dyn_graph.adjacent(v)) {
                edges_.push_back(v_adj);
            }
            vertex_begs_.push_back((int)edges_.size());
        }
    }

    int n_vertex() const {
        return (int)vertex_begs_.size() - 1;
    }
    int get_edges_count() const {
        return (int)edges_.size();
    }
    class Iterator {
      public:
        Iterator& operator++() {
            ++index_;
            return *this;
        }
        bool operator!=(const Iterator& that) const {
            assert(&edges_ == &that.edges_);
            return index_ != that.index_;
        }
        int operator*() const {
            return edges_[index_];
        }

      private:
        friend StaticGraph;
        Iterator(const std::vector<int>& edges, int index)
            : edges_(edges), index_(index) {}

      private:
        const std::vector<int>& edges_;
        int index_;
    };

  private:
    friend class EdgeGroup<StaticGraph>;
    Iterator begin_at(int edge_from) const {
        return Iterator(edges_, vertex_begs_[edge_from]);
    }
    Iterator end_at(int edge_from) const {
        return Iterator(edges_, vertex_begs_[edge_from + 1]);
    }
};

}    // namespace graph
}    // namespace doglib