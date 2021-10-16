#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct SCC {
    int N;
    vector<int> leader, leaders;
    vector<vector<int>> scc;
    vector<vector<int>> adj, rev_adj, leader_adj;
    bool built;

    SCC(int _N) : N(_N) {
        init();
    }

    SCC(const vector<vector<int>> &_adj) {
        init(_adj);
    }

    void add_directed_edge(int u, int v) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    void init() {
        adj.assign(N, {});
        rev_adj.assign(N, {});
        leader_adj.assign(N, {});
        scc.assign(N, {});
        leader.assign(N, -1);
        leaders = {};
        built = false;
    }

    void init(const vector<vector<int>> &_adj) {
        N = int(_adj.size());
        init();

        for (int v = 0; v < N; v++)
            for (int u : _adj[v])
                add_directed_edge(v, u);
    }

    void build() {
        built = true;
        leaders = {};
        leader_adj.assign(N, {});
        vector<int> order;
        vector<bool> visited(N);

        for (int v = 0; v < N; v++)
            if (!visited[v])
                dfs(v, visited, order);

        reverse(order.begin(), order.end());
        visited.assign(N, false);
        vector<int> component;

        for (int v : order)
            if (!visited[v]) {
                rev_dfs(v, visited, component);
                reverse(component.begin(), component.end());
                scc[v] = component;
                leaders.push_back(v);

                for (int node : component)
                    leader[node] = v;

                component.clear();
            }

        for (int v = 0; v < N; v++)
            for (int u : adj[v])
                if (find(u) != find(v))
                    leader_adj[find(v)].push_back(find(u));
    }

    void dfs(int v, vector<bool> &visited, vector<int> &order) {
        visited[v] = true;

        for (int u : adj[v])
            if (!visited[u])
                dfs(u, visited, order);

        order.push_back(v);
    }

    void rev_dfs(int v, vector<bool> &visited, vector<int> &component) {
        visited[v] = true;
        component.push_back(v);

        for (int u : rev_adj[v])
            if (!visited[u])
                rev_dfs(u, visited, component);
    }

    int find(int v) {
        return leader[v];
    }

    int component_size(int v) {
        assert(built);
        return int(scc[find(v)].size());
    }

    int count_components() {
        assert(built);
        return int(leaders.size());
    }

    vector<vector<int>> all_components() {
        assert(built);
        vector<vector<int>> _components;

        for (int i = 0; i < N; i++)
            if (!scc[i].empty())
                _components.push_back(scc[i]);

        return _components;
    }

    // returns components in order (if there is an edge from A to B in a condensed graph then A appears before B) in a condensed graph
    vector<vector<int>> topological_sort() {
        assert(built);
        vector<vector<int>> scc_order;
        vector<bool> visited(N, false);
        vector<int> order;

        for (int v = 0; v < N; v++)
            if (find(v) == v && !visited[v])
                order_dfs(v, visited, order);

        reverse(order.begin(), order.end());

        for (int v : order)
            scc_order.push_back(scc[v]);

        return scc_order;
    }

    void order_dfs(int v, vector<bool> &visited, vector<int> &order) {
        visited[v] = true;

        for (int u : leader_adj[v])
            if (!visited[u])
                order_dfs(u, visited, order);

        order.push_back(v);
    }
};

// tested on problems: https://cses.fi/problemset/task/1682,
//                     https://judge.yosupo.jp/problem/scc,
int main() {
    int N, M;
    cin >> N >> M;
    SCC graph(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph.add_directed_edge(u, v);
    }

    bool possible = graph.count_components() == 1;

    if (possible) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        int start = 0;

        for (int i = 0; i < N; i++)
            if (!graph.found_path(start, i)) {
                cout << start + 1 << ' ' << i + 1 << '\n';
                return 0;
            } else if (!graph.found_path(i, start)) {
                cout << i + 1 << ' ' << start + 1 << '\n';
                return 0;
            }
    }

    return 0;
}
