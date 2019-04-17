#pragma once
#include "../common/range.h"
#include "graph.h"
namespace doglib {
namespace graph {

enum class VertexStatus { Unknown, Processing, Finished };
enum class Transfer {
    discover = 0,
    finish,
    revisit_processing,
    revisit_finished,
    total_count
};
using namespace doglib::common;

class ProcedureDFS {
  public:
    ProcedureDFS(const DynamicGraph& graph)
        : graph(graph), status_vec_(graph.n_vertex(), VertexStatus::Unknown) {}

    void clear() {
        for(auto& s : status_vec_) {
            s = VertexStatus::Unknown;
        }
        todo_list_ = std::stack<pair<int, int>>();
    }

    void set_visitor(Transfer type, std::function<void(int, int)> visitor) {
        visitors_[(int)type] = visitor;
    }

    void execute_at(int source) {
        if(status_vec_[source] == VertexStatus::Unknown) {
            todo_list_.emplace(-1, source);
        }

        while(!todo_list_.empty()) {
            auto edge = todo_list_.top();
            int u = edge.first;
            int v = edge.second;
            todo_list_.pop();
            if(v < 0) {
                // finished
                v = ~v;
                visit(u, v, Transfer::finish);
                status_vec_[v] = VertexStatus::Finished;
                continue;
            }
            auto status = status_vec_[v];
            switch(status) {
                case VertexStatus::Unknown: {
                    visit(u, v, Transfer::discover);
                    status_vec_[v] = VertexStatus::Processing;
                    todo_list_.emplace(u, ~v);
                    todo_list_.emplace(u, v);
                    for(auto v_adj : graph.adjacent(v)) {
                        todo_list_.emplace(v, v_adj);
                    }
                    break;
                }
                case VertexStatus::Processing: {
                    visit(u, v, Transfer::revisit_processing);
                    break;
                }
                case VertexStatus::Finished: {
                    visit(u, v, Transfer::revisit_finished);
                    break;
                }
                default: {
                    assert(false);
                    break;
                }
            }
        }
    }

  private:
    void visit(int from, int to, Transfer type) {
        auto& visitor = visitors_[(int)type];
        if(visitor) {
            visitor(from, to);
        }
    }

  private:
    const DynamicGraph& graph;
    std::vector<VertexStatus> status_vec_;
    std::stack<pair<int, int>> todo_list_;
    std::function<void(int, int)> visitors_[(int)Transfer::total_count];
};

inline DynamicGraph transpose(const DynamicGraph& graph) {
    int nV = graph.n_vertex();
    DynamicGraph trans(nV);
    for(auto src : Range(nV)) {
        for(auto dst : graph.adjacent(src)) {
            trans.add_edge(dst, src);
        }
    }
    return std::move(trans);
}

inline std::vector<int> toposort(const DynamicGraph& graph) {
    std::vector<int> tmp;
    ProcedureDFS dfs(graph);
    dfs.set_visitor(Transfer::finish, [&](int, int v){
        tmp.push_back(v);
    });
    int N = graph.n_vertex();
    for(auto v:Range(graph.n_vertex())){
        dfs.execute_at(v);
    }
    return std::move(tmp);
}

}    // namespace graph
}    // namespace doglib
