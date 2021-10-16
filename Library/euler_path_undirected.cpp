#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>
using namespace std;

struct euler_path {
    struct edge {
        int node, id;
        edge(int _node, int _id) : node(_node), id(_id) {}
    };

    int N;
    vector<vector<edge>> adj;
    vector<int> odd_deg_nodes;

    vector<int> edge_id;
    vector<bool> used_edge;

    euler_path(int _N) : N(_N) {
        init();
    }

    void init() {
        adj.assign(N, {});
        edge_id.resize(N);
        used_edge = {};
    }

    void _add_edge(int u, int v) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        edge uv_edge(v, int(used_edge.size()));
        edge vu_edge(u, int(used_edge.size()));
        adj[u].push_back(uv_edge);
        adj[v].push_back(vu_edge);
        used_edge.push_back(false);
    }

    void add_undirected_edge(int u, int v) {
        _add_edge(u, v);
    }

    vector<int> get_path(int start = -1) {
        if (start == -1)
            start = find_positive_deg_node();

        if (start == -1 || !can_construct_path(start))
            return {};

        if (!odd_deg_nodes.empty())
            add_undirected_edge(odd_deg_nodes[0], odd_deg_nodes[1]);

        vector<int> _path = get_cycle(start);

        if (!odd_deg_nodes.empty()) {
            int node_1 = odd_deg_nodes[0];
            int node_2 = odd_deg_nodes[1];
            vector<int> new_path;
            new_path.reserve(N);

            for (int i = 0; i + 1 < int(_path.size()); i++)
                if ((node_1 == _path[i] && node_2 == _path[i + 1]) || (node_1 == _path[i + 1] && node_2 == _path[i])) {
                    for (int j = i + 1; j < int(_path.size()); j++)
                        new_path.push_back(_path[j]);

                    for (int j = 1; j <= i; j++)
                        new_path.push_back(_path[j]);

                    break;
                }

            _path.swap(new_path);
            adj[node_1].pop_back();
            adj[node_2].pop_back();
            used_edge.pop_back();
        }

        return _path;
    }

    vector<int> get_cycle(int start = -1) {
        if (start == -1)
            start = find_positive_deg_node();

        if (start == -1 || !can_construct_cycle(start))
            return {};

        edge_id.assign(N, 0);
        vector<int> _cycle;
        stack<int> st;
        st.push(start);

        while (!st.empty()) {
            while (edge_id[st.top()] < int(adj[st.top()].size())) {
                int v = st.top();

                if (!used_edge[adj[v][edge_id[v]].id]) {
                    st.push(adj[v][edge_id[v]].node);
                    used_edge[adj[v][edge_id[v]].id] = true;
                }

                edge_id[v]++;
            }

            _cycle.push_back(st.top());
            st.pop();
        }

        reverse(_cycle.begin(), _cycle.end());
        return _cycle;
    }

    bool can_construct_path(int start = -1) {
        odd_deg_nodes = {};

        if (start == -1)
            start = find_positive_deg_node();

        if (!is_connected(start))
            return false;

        for (int i = 0; i < N; i++)
            if (int(adj[i].size()) % 2 == 1)
                odd_deg_nodes.push_back(i);

        return odd_deg_nodes.empty() || int(odd_deg_nodes.size()) == 2;
    }

    bool can_construct_cycle(int start = -1) {
        odd_deg_nodes = {};

        if (start == -1)
            start = find_positive_deg_node();

        if (!is_connected(start))
            return false;

        for (int i = 0; i < N; i++)
            if (int(adj[i].size()) % 2 == 1)
                return false;

        return true;
    }

    bool is_connected(int start) {
        vector<bool> visited(N);
        dfs(start, visited);

        for (int i = 0; i < N; i++)
            if (!visited[i] && !adj[i].empty())
                return false;

        return true;
    }

    void dfs(int v, vector<bool> &visited) {
        visited[v] = true;

        for (edge &e : adj[v])
            if (!visited[e.node])
                dfs(e.node, visited);
    }

    int find_positive_deg_node() {
        for (int i = 0; i < N; i++)
            if (!adj[i].empty())
                return i;

        return -1;
    }
};

// tested on problem: https://cses.fi/problemset/task/1691
int main() {
    int N, M;
    cin >> N >> M;
    euler_path graph(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph.add_undirected_edge(u, v);
    }

    if (!graph.can_construct_cycle(0)) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> cycle = graph.get_cycle(0);

    for (int &node : cycle)
        cout << node + 1 << ' ';
    cout << '\n';

    return 0;
}
