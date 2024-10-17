#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii; // Pair of (current time, sector)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); // Improve input/output efficiency

    int n, m;
    cin >> n >> m; // Input number of sectors and corridors

    // Adjacency list to represent the graph, where each sector has a list of neighbors storing (neighbor sector, travel time)
    vector<vector<pii>> adj(n, vector<pii>());

    // Read the corridor information and build the graph
    for(int i = 0; i < m; ++i){
        int a, b, t;
        cin >> a >> b >> t;
        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t); // Assuming the corridors are undirected
    }

    // Read the lockdown times for each sector
    vector<int> lockdown(n, 0);
    for(int i = 0; i < n; ++i){
        cin >> lockdown[i];
    }

    int s, d;
    cin >> s >> d; // Starting sector and destination sector

    // Vector to store the minimum time to reach each sector, initialized to infinity
    vector<int> dist(n, numeric_limits<int>::max());
    dist[s] = 0; // Starting sector has time 0

    // Priority queue (min-heap) storing (current time, sector)
    priority_queue<pii, vector<pii>, std::greater<pii>> pq;
    pq.emplace(0, s);

    while(!pq.empty()){
        int current_time = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        // If the destination sector is reached, stop the process
        if(current == d){
            break;
        }

        // **Correction starts here**
        // Skip the sector if it is not the starting sector and the current time is greater than or equal to its lockdown time
        if(current != s && current_time >= lockdown[current]){
            continue;
        }
        // **Correction ends here**

        // Explore all neighbors of the current sector
        for(auto &edge : adj[current]){
            int neighbor = edge.first;
            int travel_time = edge.second;
            int arrival_time = current_time + travel_time;

            // Check if the arrival time at the neighbor sector is before its lockdown time
            if(arrival_time < lockdown[neighbor]){
                // If the new arrival time is shorter, update and add to the priority queue
                if(arrival_time < dist[neighbor]){
                    dist[neighbor] = arrival_time;
                    pq.emplace(arrival_time, neighbor);
                }
            }
        }
    }

    // Check if the destination sector was successfully reached
    if(dist[d] != numeric_limits<int>::max()){
        cout << dist[d];
    }
    else{
        cout << "-1";
    }

    return 0;
}