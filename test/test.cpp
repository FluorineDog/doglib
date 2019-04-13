#include "../doglib/graph/graph.h"
#include "../doglib/graph/procedure.h"
#include <vector>
#include <set>

using namespace doglib::graph;

int main() {
    DynamicGraph graph(8);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(2, 3);
    graph.add_edge(2, 4);

    graph.add_edge(7, 3);
    graph.add_edge(3, 7);

    graph.add_edge(4, 5);
    graph.add_edge(4, 6);
    graph.add_edge(6, 5);
    StaticGraph st_graph(graph);
    std::deque<int> topolist;

    {
        ProcedureDFS dfs(graph);
        dfs.set_visitor(Transfer::finish, [&](int, int v) {    //
            topolist.push_front(v);
        });

        for(int v = 0; v < graph.n_vertex(); ++v) {
            dfs.execute_at(v);
        }
    }
    std::vector<int> verify(topolist.begin(), topolist.end());
     
    DynamicGraph trans_graph(graph.n_vertex());
    for(int u = 0; u < graph.n_vertex(); ++u){
        for(auto v: graph.adjacent(u)){
            trans_graph.add_edge(v, u);
        }
    }

    std::vector<int> mapping(graph.n_vertex());
    {
        ProcedureDFS dfs(trans_graph);
        int counter = -1;
        dfs.set_visitor(Transfer::discover,  [&](int u, int v){
            if(u == -1){
                ++counter;
            }
            mapping[v] = counter;
        });
        while(!topolist.empty()){
            int v = topolist.front();
            topolist.pop_front();
            dfs.execute_at(v);
        }
    }
    int i;
    ++i;
    return 0;
}