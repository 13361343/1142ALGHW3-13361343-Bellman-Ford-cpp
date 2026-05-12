#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;


struct Edge {
    int u;   
    int v;  
    int w;   
};


struct Result {
    vector<int> dist;    
    vector<int> parent;  
    bool hasNegativeCycle;
};


Result bellmanFord(int n, const vector<Edge>& edges, int source) {

    const int INF = numeric_limits<int>::max() / 2;

    Result res;
    res.dist.assign(n, INF);
    res.parent.assign(n, -1);
    res.hasNegativeCycle = false;

    
    res.dist[source] = 0;

    
    for (int i = 1; i <= n - 1; i++) {

        for (const auto& e : edges) {

            int u = e.u;
            int v = e.v;
            int w = e.w;

         
            if (res.dist[u] != INF &&
                res.dist[u] + w < res.dist[v]) {

                res.dist[v] = res.dist[u] + w;
                res.parent[v] = u;
            }
        }
    }

    
    for (const auto& e : edges) {

        int u = e.u;
        int v = e.v;
        int w = e.w;

        if (res.dist[u] != INF &&
            res.dist[u] + w < res.dist[v]) {

            res.hasNegativeCycle = true;
        }
    }

    return res;
}


void printPath(const vector<int>& parent, int target) {

    if (target == -1)
        return;

    printPath(parent, parent[target]);

    cout << target << " ";
}


int main() {

    int n = 6; 

    
    vector<Edge> edges = {
        {0, 1, 2},
        {0, 2, 3},
        {2, 1, -2},
        {1, 3, 5},
        {3, 5, 4},
        {2, 4, 7},
        {4, 5, 1}
    };

    
    int source = 0;

   
    Result ans = bellmanFord(n, edges, source);

    
    if (ans.hasNegativeCycle) {

        cout << "Graph contains a negative-weight cycle.\n";
        return 0;
    }

    cout << "Source = " << source << "\n\n";

    
    for (int target = 0; target < n; target++) {

        cout << "Shortest distance from "
             << source
             << " to "
             << target
             << " = ";

        if (ans.dist[target] >= numeric_limits<int>::max() / 4) {

            cout << "INF\n";
        }
        else {

            cout << ans.dist[target] << "\n";

            cout << "Path: ";

            printPath(ans.parent, target);

            cout << "\n";
        }

        cout << "\n";
    }

    return 0;
}
