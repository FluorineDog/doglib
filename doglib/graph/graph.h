#pragma once
// limited to C++14
// since google codejam limits
#include <functional>
#include <algorithm>

#include <vector>
#include <queue>
#include <cassert>
#include <stack>

namespace doglib {
namespace graph {

using std::pair;

template <class Graph>
class EdgeGroup {
  public:
    EdgeGroup(const Graph& graph, int edge_from) : graph_(graph), edge_from_(edge_from) {}
    typename Graph::Iterator begin() const {
        return graph_.begin_at(edge_from_);
    }
    typename Graph::Iterator end() const {
        return graph_.end_at(edge_from_);
    }

  private:
    const Graph& graph_;
    int edge_from_;
};

class DynamicGraph {
  private:
    struct EdgeInfo {
        int to;
        int next;
        EdgeInfo(int to, int next) : to(to), next(next) {}
    };
    std::vector<int> vertex_begs_;
    std::vector<EdgeInfo> edges_;

  public:
    DynamicGraph(int n_vertex) : vertex_begs_(n_vertex, -1) {}
    void add_edge(int edge_from, int edge_to) {
        int new_slot = (int)edges_.size();
        int cur_slot = vertex_begs_[edge_from];

        // at new_slot
        edges_.emplace_back(edge_to, cur_slot);
        vertex_begs_[edge_from] = new_slot;
    }

    //@return: vertex index
    int new_vertex() {
        int id = n_vertex();
        vertex_begs_.emplace_back(-1);
        return id;
    }

    int n_vertex() const {
        return (int)vertex_begs_.size();
    }

    int get_edges_count() const {
        return (int)edges_.size();
    }

    class Iterator {
      public:
        Iterator& operator++() {
            index_ = edges_[index_].next;
            return *this;
        }
        bool operator!=(Iterator& that) const {
            assert(&edges_ == &that.edges_);
            return index_ != that.index_;
        }

        int operator*() const {
            return edges_[index_].to;
        }

      private:
        friend DynamicGraph;
        Iterator(const std::vector<EdgeInfo>& edges_, int index = -1)
            : edges_(edges_), index_(index) {}

      private:
        const std::vector<EdgeInfo>& edges_;
        int index_;
    };

    EdgeGroup<DynamicGraph> adjacent(int edge_from) const {
        return EdgeGroup<DynamicGraph>(*this, edge_from);
    }

  private:
    friend class EdgeGroup<DynamicGraph>;
    Iterator begin_at(int edge_from) const {
        return Iterator(edges_, vertex_begs_[edge_from]);
    }
    Iterator end_at(int) const {
        return Iterator(edges_, -1);
    }
};

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