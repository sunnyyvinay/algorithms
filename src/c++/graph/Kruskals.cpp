#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Comparator function to sort edges by weight
bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

// Find the root of a set (with path compression)
int find(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

// Union of two sets
void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

/*
 * Kruskal's ALGORITHM
 *
 * Finds the minimum spanning tree of a graph by sorting the edges and adding an edge only if it doesn't cause a cycle.
 * This implementation uses a union-find data structure with 3 operations (make, find, and union)
 *
 * Time complexity: O(V*log(E))
 *
*/

// Function to find the MST using Kruskal's Algorithm
void kruskalMST(vector<Edge> &edges, int V) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Parent and rank arrays for union-find
    vector<int> parent(V);
    vector<int> rank(V, 0);

    // Initialize parent array (each node is its own parent)
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    vector<Edge> result; // Store the edges of the MST
    int mstWeight = 0;

    for (const auto &edge : edges) {
        int srcParent = find(parent.data(), edge.src);
        int destParent = find(parent.data(), edge.dest);

        // If including this edge doesn't form a cycle
        if (srcParent != destParent) {
            result.push_back(edge);
            mstWeight += edge.weight;
            unionSets(parent.data(), rank.data(), edge.src, edge.dest);
        }
    }

    // Output the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : result) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << '\n';
    }
    cout << "Total weight of MST: " << mstWeight << '\n';
}

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    vector<Edge> edges = {
            {0, 1, 10},
            {0, 2, 6},
            {0, 3, 5},
            {1, 3, 15},
            {2, 3, 4}
    };

    kruskalMST(edges, V);

    return 0;
}