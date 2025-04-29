#include<iostream>             // For standard input and output
#include <vector>              // For using vectors to store edges
#include <climits>            // For using INT_MAX as infinite
#include <cstring>            // For memset if needed
#include <algorithm>          // For sorting edges in Kruskal's algorithm
#define INF INT_MAX           // Define INF as maximum integer value to represent no edge

using namespace std;

// Structure to represent an edge for Kruskal's algorithm
struct Edge {
    int src, dest, weight;    // src = source, dest = destination, weight = edge weight
};

// Function to find the root of a set (with path compression)
int findParent(int parent[], int i) {
    if (parent[i] != i)              // If i is not the root of its set
        parent[i] = findParent(parent, parent[i]); // Recursively find root and compress path
    return parent[i];                // Return root
}

// Function to do union of two sets (by rank)
void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = findParent(parent, x); // Find root of x
    int yroot = findParent(parent, y); // Find root of y

    // Attach smaller rank tree under root of higher rank tree
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot; // Arbitrarily attach y to x
        rank[xroot]++;         // Increase rank of new root
    }
}

int main() {
    int V;                     // Number of vertices
    cin >> V;

    int graph[V][V];           // Adjacency matrix of the graph
    vector<Edge> edges;        // To store edges for Kruskal's algorithm

    // Taking input and preparing graph is skipped as per your request

    int parent[V];             // Stores parent of each vertex in the MST
    int key[V];                // Stores minimum edge weight to connect to MST
    bool mstSet[V];            // true if vertex is included in MST

    for (int i = 0; i < V; ++i) {
        key[i] = INF;          // Initialize all key values to INF
        mstSet[i] = false;     // Initially, no vertex is in MST
    }

    key[0] = 0;                // Start from the first vertex (key = 0 so it's picked first)
    parent[0] = -1;            // Root node has no parent

    // Run the algorithm V-1 times (MST has V-1 edges)
    for (int count = 0; count < V - 1; ++count) {
        int u = -1;            // To store index of minimum key vertex not in MST

        // Find the vertex with the minimum key not yet in MST
        for (int v = 0; v < V; ++v) {
            if (!mstSet[v]) {
                if (u == -1 || key[v] < key[u]) {
                    u = v;     // Update u to the new minimum key vertex
                }
            }
        }

        mstSet[u] = true;      // Include the selected vertex in MST

        // Update keys and parent of all adjacent vertices
        for (int v = 0; v < V; ++v) {
            // Update only if there is an edge and vertex v is not in MST and weight is smaller
            if (graph[u][v] != INF && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;         // Update parent to u
                key[v] = graph[u][v];  // Update key to the new minimum weight
            }
        }
    }

    cout << "\n--- Prim's Algorithm ---\n";
    cout << "Edges in MST:\n";
    int minCost = 0;                    // To store total weight of MST

    // Print the MST stored in parent[]
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " Weight = " << graph[i][parent[i]] << endl;
        minCost += graph[i][parent[i]];  // Add weight to total cost
    }

    cout << "Cost of Minimum Spanning Tree (Prim's): " << minCost << endl;

    // Sort all edges by increasing weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    vector<Edge> result;       // To store final MST edges
    int parentK[V];            // Parent array for union-find
    int rank[V];               // Rank array to keep union tree balanced

    for (int i = 0; i < V; i++) {
        parentK[i] = i;        // Initially, each vertex is its own parent
        rank[i] = 0;           // Rank is 0 for all
    }

    int edgeCount = 0;         // Number of edges included in MST
    int kruskalCost = 0;       // Total cost of MST

    // Iterate over sorted edges
    for (Edge e : edges) {
        int u = findParent(parentK, e.src);   // Find root of source
        int v = findParent(parentK, e.dest);  // Find root of destination

        // If including this edge doesn't form a cycle
        if (u != v) {
            result.push_back(e);              // Add edge to MST
            kruskalCost += e.weight;          // Add weight to total cost
            unionSets(parentK, rank, u, v);   // Union the two sets
            edgeCount++;                      // Increment edge count
            if (edgeCount == V - 1) break;    // Stop if MST is complete
        }
    }

    cout << "\n--- Kruskal's Algorithm ---\n";
    cout << "Edges in MST:\n";

    // Print the MST edges
    for (auto e : result) {
        cout << e.src << " - " << e.dest << " Weight = " << e.weight << endl;
    }

    cout << "Cost of Minimum Spanning Tree (Kruskal's): " << kruskalCost << endl;

    return 0;  // End of program
}
