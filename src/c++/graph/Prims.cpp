#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Edge {
public:
    int weight = 0;
    int to = 0; // node

    Edge(int to, int weight) {
        this->weight = weight;
        this->to = to;
    }
};

vector<vector<Edge*>> findMST(vector<vector<Edge*>>& graph, int startNode);

/*
 * Prim's ALGORITHM
 *
 * Finds the minimum spanning tree of a graph by adding edges with the minimum attachment cost to the MST.
 * This implementation uses a priority queue.
 *
 * Time complexity: O(E*log(V))
 *
*/

vector<vector<Edge*>> findMST(vector<vector<Edge*>>& graph, int startNode) {
    int n = graph.size();
    // Min-heap with pair <attachment cost, { node, parent }>
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<pair<int, vector<int>>>> P;
    vector<bool> visited(n);

    vector<vector<Edge*>> T(n); // MST result
    int totalWeight = 0;

    P.push(pair<int, vector<int>>(0, { startNode, -1 }));
    while (!P.empty()) {
        pair<int, vector<int>> entry = P.top();
        int weight = entry.first;
        int node = entry.second[0];
        int parent = entry.second[1];
        P.pop();

        if (visited[node]) continue;

        visited[node] = true;

        if (parent != -1) {
            totalWeight += weight;
            T[parent].push_back(new Edge(node, weight));
            T[node].push_back(new Edge(parent, weight));
        }

        for (auto neighbor : graph[node]) {
            if (!visited[neighbor->to]) {
                P.push(pair<int, vector<int>>(neighbor->weight, { neighbor->to, node }));
            }
        }
    }

    cout << "MST weight: " << totalWeight << endl;

    return T;
}

int main() {
    vector<vector<Edge*>> graph = {
            {new Edge(1, 2), new Edge(2, 2)},                               // Node 0 is connected to nodes 1, 2
            {new Edge(0, 2), new Edge(4, 5), new Edge(3, 2)},    // Node 1 is connected to nodes 0, 3, 4
            {new Edge(0, 2), new Edge(4, 2)},                               // Node 2 is connected to nodes 0, 4
            {new Edge(1, 2), new Edge(4, 2)},                               // Node 3 is connected to node 1, 4
            {new Edge(1, 5), new Edge(3, 2), new Edge(2, 2)}     // Node 4 is connected to node 1, 2, 3
    };

    vector<vector<Edge*>> T = findMST(graph, 0);

    return 0;
}