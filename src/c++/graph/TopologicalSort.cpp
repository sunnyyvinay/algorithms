#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
 * Topological Sort ALGORITHM
 *
 * Sorts vertices based on their order of dependencies.
 * Only works for directed, acyclic graphs (DAGs).
 *
 * Time complexity: O(V + E)
 *
 */

void topologicalSort(vector<vector<int>>& L_in, vector<vector<int>>& L_out, int n) {
    vector<int> in_deg(n, -1);
    queue<int> Q;

    for (int i = 0; i < n; i++) {
        in_deg[i] = L_in[i].size();
        if (in_deg[i] == 0) Q.push(i);
    }

    while (!Q.empty()) {
        int i = Q.front();
        Q.pop();
        cout << i << " ";

        for (int neighbor : L_out[i]) {
            in_deg[neighbor]--;
            if (in_deg[neighbor] == 0) Q.push(neighbor);
        }
    }
}

int main() {
    int n = 4; // number of nodes

    // L_in[i] = vertices that go into vertex i
    vector<vector<int>> L_in = {
            {},
            {0, 3},
            {1, 3},
            {}
    };
    // L_out[i] = vertices that go out of vertex i
    vector<vector<int>> L_out = {
            {1},
            {2},
            {},
            {1, 2}
    };

    cout << "Topological sorting of the graph: ";
    topologicalSort(L_in, L_out, n);
    cout << endl;

    return 0;
}