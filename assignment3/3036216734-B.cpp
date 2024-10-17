#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii; // Pair of (distance, sector)

int main(){
    int n, m;
    cin >> n >> m; // Number of sectors and corridors

    // Adjacency list: each sector has a list of pairs (neighbor, travel time)
    vector<vector<pii>> adj(n, vector<pii>());

    // Reading corridors and building the graph
    for(int i = 0; i < m; ++i){
        int a, b, t;
        cin >> a >> b >> t;
        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t); // Assuming corridors are undirected
    }

    int s, d;
    cin >> s >> d; // Starting sector and destination sector

    // Vector to store the minimum time to reach each sector
    vector<int> dist(n, numeric_limits<int>::max());
    dist[s] = 0; // Starting sector has distance 0

    // Min-heap priority queue (distance, sector)
    priority_queue<pii, vector<pii>, std::greater<pii>> pq;
    pq.emplace(0, s);

    while(!pq.empty()){
        int current_dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        // If we've reached the destination, no need to continue
        if(current == d){
            break;
        }

        // Explore all neighbors
        for(auto &edge : adj[current]){
            int neighbor = edge.first;
            int time = edge.second;

            // If a shorter path to neighbor is found
            if(current_dist + time < dist[neighbor]){
                dist[neighbor] = current_dist + time;
                pq.emplace(dist[neighbor], neighbor);
            }
        }
    }

    // If destination is reachable, output the minimum time; else, -1
    if(dist[d] != numeric_limits<int>::max()){
        cout << dist[d];
    }
    else{
        cout << "-1";
    }

    return 0;
}