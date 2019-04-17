#include "../common/common.h"
#include "../graph/graph.h"

void fuck(const vector<vector<double>>& table, int n_src, int n_dest) {
    //    std::priority_queue<pair<int> hhd;
    assert(n_src < n_dest);
    vector<int> reverse_matching(n_src, -1);
    vector<int> matching(n_dest, -1);
    while(true) {
        vector<pair<int, double>> recorder(-2, 0.0);
        std::priority_queue<tuple<double, int>> wtf;
        for(auto s : Range(n_src)) {
            if(matching[s] != -1) {
                wtf.emplace(0, -1, ~s);
            }
        }
        while(!wtf.empty()){
            int cur = wtf.top();
            if(cur < 0){
                // cur is S
                cur = ~cur;
                for(auto d: Range(table)){
                    if(matching[])
                }
            }
        }
    }
}