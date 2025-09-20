#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

const int INF = numeric_limits<int>::max();
//Add Comment
class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int v) : vertices(v) {
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // For undirected graph
    }

    void dijkstra(int start) {
        vector<int> dist(vertices, INF);
        vector<int> prev(vertices, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest distances from node " << start << ":" << endl;
        for (int i = 0; i < vertices; ++i) {
            cout << "To node " << i << ": " << (dist[i] == INF ? -1 : dist[i]) << endl;
        }

        cout << "\nPaths:" << endl;
        for (int i = 0; i < vertices; ++i) {
            if (i == start) continue;
            cout << "Path to " << i << ": ";
            printPath(prev, i);
            cout << endl;
        }
    }

    void printPath(vector<int>& prev, int target) {
        if (prev[target] == -1) {
            cout << target;
            return;
        }
        printPath(prev, prev[target]);
        cout << " -> " << target;
    }
};

void displayMenu() {
    cout << "=== Dijkstra's Algorithm ===" << endl;
    cout << "1. Add edge" << endl;
    cout << "2. Run Dijkstra" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            int u, v, w;
            cout << "Enter edge (u v weight): ";
            cin >> u >> v >> w;
            g.addEdge(u, v, w);
        } else if (choice == 2) {
            int start;
            cout << "Enter starting node: ";
            cin >> start;
            g.dijkstra(start);
        } else if (choice == 3) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
