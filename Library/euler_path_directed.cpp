#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>
using namespace std;

struct euler_path {
    int N;
    vector<vector<int>> adj;
    vector<int> indeg, outdeg;
    vector<int> edge_id;

    euler_path(int _N) : N(_N) {
        init();
    }

    euler_path(const vector<vector<int>> &_adj) {
        init(_adj);
    }

    void init() {
        adj.assign(N, {});
        indeg.assign(N, 0);
        outdeg.assign(N, 0);
        edge_id.resize(N);
    }

    void init(const vector<vector<int>> &_adj) {
        N = int(_adj.size());
        init();

        for (int v = 0; v < N; v++)
            for (int u : _adj[v])
                add_directed_edge(v, u);
    }

    void add_directed_edge(int u, int v) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        adj[u].push_back(v);
        outdeg[u]++; indeg[v]++;
    }

    vector<int> get_path() {
        if (!can_construct_path())
            return {};

        int start = find_positive_outdeg_node();
        assert(start >= 0);

        for (int v = 0; v < N; v++)
            if (outdeg[v] - indeg[v] == 1)
                start = v;

        edge_id.assign(N, 0);
        vector<int> _path;
        stack<int> st;
        st.push(start);

        while (!st.empty()) {
            while (edge_id[st.top()] < int(adj[st.top()].size())) {
                int v = st.top();
                st.push(adj[v][edge_id[v]]);
                edge_id[v]++;
            }

            _path.push_back(st.top());
            st.pop();
        }

        reverse(_path.begin(), _path.end());
        return _path;
    }

    vector<int> get_cycle(int start = -1) {
        if (start == -1)
            start = find_positive_outdeg_node();

        if (!can_construct_cycle(start))
            return {};

        edge_id.assign(N, 0);
        vector<int> _cycle;
        stack<int> st;
        st.push(start);

        while (!st.empty()) {
            while (edge_id[st.top()] < int(adj[st.top()].size())) {
                int v = st.top();
                st.push(adj[v][edge_id[v]]);
                edge_id[v]++;
            }

            _cycle.push_back(st.top());
            st.pop();
        }

        reverse(_cycle.begin(), _cycle.end());
        return _cycle;
    }

    bool can_construct_path() {
        vector<int> indeg_nodes, outdeg_nodes;

        for (int v = 0; v < N; v++) {
            if (abs(indeg[v] - outdeg[v]) > 1)
                return false;
            if (indeg[v] - outdeg[v] == 1)
                indeg_nodes.push_back(v);
            if (outdeg[v] - indeg[v] == 1)
                outdeg_nodes.push_back(v);
        }

        if (indeg_nodes.size() != outdeg_nodes.size() || int(indeg_nodes.size()) > 1 || int(outdeg_nodes.size()) > 1)
            return false;

        vector<int> order;
        vector<bool> visited(N, false);

        // makes a topological sort
        for (int v = 0; v < N; v++)
            if (!visited[v])
                dfs(v, visited, order);

        reverse(order.begin(), order.end());
        visited.assign(N, false);

        // runs dfs from the first node that has at least one directed edge and then breaks
        for (int v : order)
            if (!adj[v].empty()) {
                dfs(v, visited);
                break;
            }

        for (int v = 0; v < N; v++)
            if (!visited[v] && !adj[v].empty())
                return false;

        return true;
    }

    bool can_construct_cycle(int start = -1) {
        // checks for the most important condition for possible construction of a cycle -> indegree of a node MUST BE EQUAL to the outdegree
        for (int v = 0; v < N; v++)
            if (indeg[v] != outdeg[v])
                return false;

        // if the start of the cycle is not given then we can choose arbitrarily
        if (start == -1)
            start = find_positive_outdeg_node();

        assert(start >= 0);
        vector<bool> visited(N, false);
        dfs(start, visited);

        // checks for isolated components that are of size >= 2
        for (int v = 0; v < N; v++)
            if (!visited[v] && !adj[v].empty())
                return false;

        return true;
    }

    void dfs(int v, vector<bool> &visited, vector<int> &order) {
        visited[v] = true;

        for (int u : adj[v])
            if (!visited[u])
                dfs(u, visited, order);

        order.push_back(v);
    }

    void dfs(int v, vector<bool> &visited) {
        visited[v] = true;

        for (int u : adj[v])
            if (!visited[u])
                dfs(u, visited);
    }

    int find_positive_outdeg_node() {
        for (int v = 0; v < N; v++)
            if (!adj[v].empty())
                return v;

        return -1;
    }
};

// tested on problem: https://cses.fi/problemset/task/1693
int main() {
    int N, M;
    cin >> N >> M;
    euler_path graph(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph.add_directed_edge(u, v);
    }

    if (!graph.can_construct_path()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path = graph.get_path();

    if (path.front() != 0 || path.back() != N - 1) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < int(path.size()); i++)
            cout << path[i] + 1 << (i + 1 < int(path.size()) ? ' ' : '\n');
    }

    return 0;
}
