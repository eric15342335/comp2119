#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii; // Pair of (current time, sector)

int main(){
    int n, m;
    cin >> n >> m; // Number of sectors and corridors

    // Adjacency list representation of the graph
    vector<vector<int>> adj(n, vector<int>(n, 0));

    // input corridors
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        adj[a][b] = t;
        adj[b][a] = t;
    }

    // Read the lockdown times for each sector
    vector<int> lockdown(n, 0);
    for(int i = 0; i < n; ++i){
        cin >> lockdown[i];
    }

    int s, d;
    cin >> s >> d; // Starting sector and destination sector

    // Vector to store the minimum time to reach each sector
    vector<int> dist(n, numeric_limits<int>::max());

    // priority queue (distance, sector)
    priority_queue<pii, vector<pii>, std::greater<pii>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int target_sector = pq.top().second;
        int target_distance = pq.top().first;
        pq.pop();

        if (target_distance < dist[target_sector]) {
            dist[target_sector] = target_distance;

            for (int i = 0; i < n; i++) {
                // modification from part b:
                // check if the corridor is available and the time to reach the sector is less than the lockdown time
                if (adj[target_sector][i] > 0 && target_distance + adj[target_sector][i] < lockdown[i]) {
                    pq.push({target_distance + adj[target_sector][i], i});
                }
            }
        }
    }

    if (dist[d] == numeric_limits<int>::max()) {
        cout << -1 << endl;
    } else {
        cout << dist[d] << endl;
    }
    return 0;
}