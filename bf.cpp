#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFordDP(vector<Edge>& edges, int V, int source) {
    // DP table: dp[i][v] = shortest distance to vertex v using at most i edges
    vector<vector<int>> dp(V, vector<int>(V, INT_MAX));
    
    // Base case: distance to source is 0
    for (int i = 0; i < V; i++) {
        dp[i][source] = 0;
    }
    
    // Fill DP table
    // For each number of edges (0 to V-1)
    for (int i = 1; i < V; i++) {
        // Copy previous values
        for (int v = 0; v < V; v++) {
            dp[i][v] = dp[i-1][v];
        }
        
        // Try to improve using each edge
        for (int j = 0; j < edges.size(); j++) {
            if (dp[i-1][edges[j].src] != INT_MAX) {
                int newDist = dp[i-1][edges[j].src] + edges[j].weight;
                if (newDist < dp[i][edges[j].dest]) {
                    dp[i][edges[j].dest] = newDist;
                }
            }
        }
    }
    
    // Check for negative cycle
    bool hasNegativeCycle = false;
    for (int i = 0; i < edges.size(); i++) {
        if (dp[V-1][edges[i].src] != INT_MAX) {
            if (dp[V-1][edges[i].src] + edges[i].weight < dp[V-1][edges[i].dest]) {
                hasNegativeCycle = true;
                break;
            }
        }
    }
    
    // Print results
    if (hasNegativeCycle) {
        cout << "Graph contains negative weight cycle!" << endl;
    } else {
        cout << "Shortest distances from source " << source << ":" << endl;
        for (int i = 0; i < V; i++) {
            if (dp[V-1][i] == INT_MAX) {
                cout << "Vertex " << i << ": INF" << endl;
            } else {
                cout << "Vertex " << i << ": " << dp[V-1][i] << endl;
            }
        }
    }
}

int main() {
    int V = 5; // Number of vertices
    vector<Edge> edges;
    
    // Add edges (source, destination, weight)
    edges.push_back({0, 1, -1});
    edges.push_back({0, 2, 4});
    edges.push_back({1, 2, 3});
    edges.push_back({1, 3, 2});
    edges.push_back({1, 4, 2});
    edges.push_back({3, 2, 5});
    edges.push_back({3, 1, 1});
    edges.push_back({4, 3, -3});
    
    int source = 0;
    bellmanFordDP(edges, V, source);
    
    return 0;
}
