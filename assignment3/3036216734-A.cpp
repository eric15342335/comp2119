#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // Number of sectors and corridors

    // Adjacency list representation of the graph
    vector<vector<int>> adj(n, vector<int>());

    // Reading corridors and building the graph
    for(int i = 0; i < m; ++i){
        int a, b, t;
        cin >> a >> b >> t;
        // Assuming corridors are undirected
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int s;
    cin >> s; // Starting sector

    // Vector to keep track of visited sectors
    vector<bool> visited(n, false);

    // BFS queue
    queue<int> q;
    q.push(s);
    visited[s] = true;

    // Perform BFS
    while(!q.empty()){
        int current = q.front();
        q.pop();

        // Visit all adjacent sectors
        for(auto &neighbor : adj[current]){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // Count the number of sectors not visited (unreachable)
    int p = 0;
    for(int i = 0; i < n; ++i){
        if(!visited[i]) p++;
    }

    cout << p; // Output the result

    return 0;
}
