#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cassert>
using namespace std;

template<typename flow_t>struct dinic {
    struct edge {
        int node, rev;
        flow_t cap;
        edge(int _node, int _rev, flow_t _cap) : node(_node), rev(_rev), cap(_cap) {}
    };

    int V;
    vector<int> dist;
    vector<int> edge_id;
    vector<vector<edge>> adj;
    bool flow_called;

    dinic(int _V) : V(_V) {
        init();
    }

    void init() {
        adj.assign(V, {});
        dist.resize(V);
        edge_id.resize(V);
        flow_called = false;
    }

    void _add_edge(int u, int v, flow_t cap1, flow_t cap2) {
        assert(cap1 >= 0 && cap2 >= 0);
        assert(0 <= u && u < V && 0 <= v && v < V);
        edge uv_edge(v, int(adj[v].size()) + (u == v), cap1);
        edge vu_edge(u, int(adj[u].size()), cap2);
        adj[u].push_back(uv_edge);
        adj[v].push_back(vu_edge);
    }

    void add_directed_edge(int u, int v, flow_t cap) {
        _add_edge(u, v, cap, 0);
    }

    void add_undirected_edge(int u, int v, flow_t cap) {
        _add_edge(u, v, cap, cap);
    }

    edge& rev_edge(const edge &e) {
        return adj[e.node][e.rev];
    }

    flow_t flow(int source, int sink) {
        flow_called = true;
        flow_t total_flow = 0;

        while (bfs(source, sink)) {
            edge_id.assign(V, 0);
            total_flow += dfs(source, sink, numeric_limits<flow_t>::max());
        }

        return total_flow;
    }

    bool bfs(int source, int sink) {
        dist.assign(V, -1);
        dist[source] = 0;
        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int v = q.front(); q.pop();

            for (edge &e : adj[v])
                if (e.cap > 0 && dist[e.node] == -1) {
                    dist[e.node] = dist[v] + 1;
                    q.push(e.node);
                }
        }

        return dist[sink] != -1;
    }

    flow_t dfs(int v, int sink, flow_t inc_flow) {
        if (v == sink)
            return inc_flow;

        if (dist[v] >= dist[sink])
            return 0;

        flow_t total_flow = 0;

        while (edge_id[v] < int(adj[v].size())) {
            edge &e = adj[v][edge_id[v]];

            if (e.cap > 0 && dist[e.node] > dist[v]) {
                flow_t pushed_flow = dfs(e.node, sink, min(inc_flow, e.cap));
                e.cap -= pushed_flow;
                rev_edge(e).cap += pushed_flow;
                inc_flow -= pushed_flow;
                total_flow += pushed_flow;
            }

            if (inc_flow == 0)
                break;

            edge_id[v]++;
        }

        return total_flow;
    }

    // return a list of edge {capacity, {from_node, to_node}}
    // TODO: for undirected edges, resulting capacities DIVIDE BY 2
    vector<pair<flow_t, pair<int, int>>> min_cut(int source) {
        assert(flow_called);
        vector<bool> reachable(V, false);
        vector<pair<flow_t, pair<int, int>>> cut;
        reachable_dfs(source, reachable);

        for (int v = 0; v < V; v++)
            if (reachable[v])
                for (edge &e : adj[v])
                    if (!reachable[e.node])
                        cut.emplace_back(rev_edge(e).cap, make_pair(v, e.node));

        return cut;
    }

    void reachable_dfs(int v, vector<bool> &visited) {
        visited[v] = true;

        for (edge &e : adj[v])
            if (e.cap > 0 && !visited[e.node])
                reachable_dfs(e.node, visited);
    }

    // returns list of pairs {left_side_node, right_side_node}
    // works only if left nodes are from 0 to L - 1 and right nodes are from L to L + R
    vector<pair<int, int>> max_matching(int L, int R) {
        assert(flow_called);
        vector<pair<int, int>> matching;

        for (int l = 0; l < L; l++)
            for (edge &e : adj[l])
                if (e.cap == 0 && L <= e.node && e.node < L + R)
                    matching.emplace_back(l, e.node - L);

        return matching;
    }
};

// tested on problems: https://cses.fi/problemset/task/1694,
//                     https://cses.fi/problemset/task/1695,
//                     https://cses.fi/problemset/task/1696,
//                     https://judge.yosupo.jp/problem/bipartitematching,
int main() {
    int N, M, K;
    cin >> N >> M >> K;
    dinic<int> graph(N + M + 2);
    int source = N + M, sink = N + M + 1;

    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        a--; b = b - 1 + N;
        graph.add_directed_edge(a, b, 1);
    }

    for (int i = 0; i < N; i++)
        graph.add_directed_edge(source, i, 1);

    for (int i = N; i < N + M; i++)
        graph.add_directed_edge(i, sink, 1);

    cout << graph.flow(source, sink) << '\n';
    vector<pair<int, int>> pairs = graph.max_matching(N, M);

    for (auto &p : pairs)
        cout << p.first + 1 << ' ' << p.second - N + 1 << '\n';
}
