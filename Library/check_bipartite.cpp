#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

struct check_bipartite {
    int N;
    vector<bool> color;
    vector<bool> visited;
    vector<vector<int>> adj;

    check_bipartite(int _N) : N(_N) {
        init();
    }

    check_bipartite(const vector<vector<int>> &_adj) : adj(_adj) {
        N = int(_adj.size());
        visited.resize(N);
        color.resize(N);
    }

    void init() {
        adj.assign(N, {});
        visited.resize(N);
        color.resize(N);
    }

    void add_directed_edge(int u, int v) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        adj[u].push_back(v);
    }

    void add_undirected_edge(int u, int v) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool is_bipartite() {
        visited.assign(N, false);
        color.assign(N, false);
        bool bipartite = true;

        for (int i = 0; i < N; i++)
            if (!visited[i])
                bipartite &= bfs(i);

        return bipartite;
    }

    bool bfs(int start) {
        assert(0 <= start && start < N);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int u : adj[v]) {
                if (visited[u] && color[u] == color[v])
                    return false;

                if (!visited[u]) {
                    visited[u] = true;
                    color[u] = !color[v];
                    q.push(u);
                }
            }
        }

        return true;
    }
};

// tested on problems: https://www.spoj.com/problems/BUGLIFE/,
//                     https://cses.fi/problemset/task/1668,
int main() {
    int N, M;
    cin >> N >> M;
    check_bipartite graph(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph.add_undirected_edge(u, v);
    }

    if (!graph.is_bipartite()) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < N; i++)
            cout << 1 + graph.color[i] << ' ';
        cout << '\n';
    }

}
