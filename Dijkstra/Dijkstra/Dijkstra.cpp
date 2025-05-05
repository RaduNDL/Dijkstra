#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <set>
#include <random>
#include <chrono>
using namespace std;
const int INF = INT_MAX;
void dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src, const string& filename) {
    vector<int> dist(V, INF); 
    dist[src] = 0; 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    pq.push({ 0, src }); 
    while (!pq.empty()) { 
        int u = pq.top().second; 
        int d = pq.top().first; 
        pq.pop(); 
        if (d > dist[u]) continue; 
        for (auto& neighbor : adj[u]) { 
            int v = neighbor.first; 
            int weight = neighbor.second; 
            if (dist[u] + weight < dist[v]) { 
                dist[v] = dist[u] + weight; 
                pq.push({ dist[v], v }); 
            }
        }
    }
    ofstream fout(filename); 
    if (!fout) { 
        cerr << "Error opening file for writing." << endl;
        return;
    }
    for (int i = 0; i < V; i++) { 
        fout << i << " " << (dist[i] == INF ? -1 : dist[i]) << endl;
    }
    fout.close(); 
    cout << "Distances have been saved to " << filename << endl; 
}
int main() {
    int V = 10000;  
    int E = 100000; 
    vector<vector<pair<int, int>>> adj(V); 
    mt19937 rng(123);  
    uniform_int_distribution<int> dist_node(0, V - 1);  
    uniform_int_distribution<int> dist_weight(1, 100);  
    auto start = chrono::high_resolution_clock::now(); 
    set<pair<int, int>> addedEdges;  
    for (int i = 0; i < E; ++i) { 
        int u = dist_node(rng); 
        int v = dist_node(rng); 
        if (u != v) { 
            if (addedEdges.find({ u, v }) == addedEdges.end() && addedEdges.find({ v, u }) == addedEdges.end()) {
                int w = dist_weight(rng);
                adj[u].push_back({ v, w }); 
                addedEdges.insert({ u, v }); 
            }
        }
    }
    dijkstra(V, adj, 0, "distances.txt"); 
    auto end = chrono::high_resolution_clock::now(); 
    chrono::duration<double> duration = end - start; 
    cout << "Total Execution Time: " << duration.count() << " seconds" << endl;
    return 0;
}
