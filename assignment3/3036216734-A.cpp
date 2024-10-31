#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
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

    int s;
    cin >> s; // Starting sector

    vector<int> visited(n, 0);
    queue<int> to_visit;
    to_visit.push(s);

    // breadth first search
    while (to_visit.size() > 0) {
        // queue.pop does not return the value
        int current = to_visit.front();
        to_visit.pop();
        // Mark as visited
        visited[current] = 1;

        // check whether corridor is available to other sectors
        for (int i = 0; i < n; i++) {
            if (adj[current][i] > 0 && visited[i] == 0) {
                to_visit.push(i);
            }
        }
    }

    // count unreachable sectors
    int unreachable = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            unreachable++;
        }
    }

    cout << unreachable << endl;
    return 0;
}
