#include "doglib/graph/graph.h"
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
    return 0; 
}