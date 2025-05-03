#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
#define INF INT_MAX

using namespace std;

struct Edge {
    int src, dest, weight;
};

// Path compression
int findParent(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = findParent(parent, parent[i]);
    return parent[i];
}

// Union by rank
void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Prim's Algorithm
void primMST(int V, int graph[100][100]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!mstSet[v]) {
                if (u == -1 || key[v] < key[u]) {
                    u = v;
                }
            }
        }

        mstSet[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != INF && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "\n--- Prim's Algorithm ---\n";
    cout << "Edges in MST:\n";
    int minCost = 0;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " Weight = " << graph[i][parent[i]] << endl;
        minCost += graph[i][parent[i]];
    }
    cout << "Cost of Minimum Spanning Tree (Prim's): " << minCost << endl;
}

// Kruskal's Algorithm
void kruskalMST(int V, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    int parent[V], rank[V];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    vector<Edge> result;
    int edgeCount = 0, kruskalCost = 0;

    for (Edge e : edges) {
        int u = findParent(parent, e.src);
        int v = findParent(parent, e.dest);

        if (u != v) {
            result.push_back(e);
            kruskalCost += e.weight;
            unionSets(parent, rank, u, v);
            edgeCount++;
            if (edgeCount == V - 1) break;
        }
    }

    cout << "\n--- Kruskal's Algorithm ---\n";
    cout << "Edges in MST:\n";
    for (auto e : result) {
        cout << e.src << " - " << e.dest << " Weight = " << e.weight << endl;
    }
    cout << "Cost of Minimum Spanning Tree (Kruskal's): " << kruskalCost << endl;
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    int graph[100][100];
    vector<Edge> edges;

    cout << "Enter adjacency matrix (enter INF = " << INF << " for no edge):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> graph[i][j];
            if (i < j && graph[i][j] != INF) {
                Edge e = {i, j, graph[i][j]};
                edges.push_back(e);
            }
        }
    }

    int choice;
    do {
        cout << "\nMenu:\n1. Prim's Algorithm\n2. Kruskal's Algorithm\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                primMST(V, graph);
                break;
            case 2:
                kruskalMST(V, edges);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
