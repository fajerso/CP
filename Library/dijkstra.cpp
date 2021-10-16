#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>
#include <cassert>
using namespace std;

const int64_t INF = int64_t(1e18) + 15;

template<typename T>struct dijkstra {
    struct edge {
        int node;
        T w;
        edge(int _node, T _w) : node(_node), w(_w) {}
    };

    int N;
    vector<T> dist;
    vector<int> parent;
    vector<vector<edge>> adj;
    bool ran_dijkstra;

    dijkstra(int _N) : N(_N) {
        init();
    }

    void init() {
        adj.assign(N, {});
        dist.resize(N);
        parent.resize(N);
        ran_dijkstra = false;
    }

    void add_directed_edge(int u, int v, T w) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        assert(w >= 0);
        adj[u].push_back(edge(v, w));
    }

    void add_undirected_edge(int u, int v, T w) {
        assert(0 <= u && u < N && 0 <= v && v < N);
        assert(w >= 0);
        adj[u].push_back(edge(v, w));
        adj[v].push_back(edge(u, w));
    }

    void run_dijkstra(int start) {
        assert(0 <= start && start < N);
        ran_dijkstra = true;
        dist.assign(N, INF);
        parent.assign(N, -1);
        dist[start] = 0;

        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int v = pq.top().second;
            T d = pq.top().first;
            pq.pop();

            if (d > dist[v])
                continue;

            for (edge &e : adj[v])
                if (d + e.w < dist[e.node]) {
                    dist[e.node] = d + e.w;
                    parent[e.node] = v;
                    pq.push({dist[e.node], e.node});
                }
        }
    }

    T distance(int end) {
        assert(ran_dijkstra);
        return dist[end];
    }

    vector<int> get_path(int end) {
        assert(ran_dijkstra);
        vector<int> _path;

        for (int v = end; v != -1; v = parent[v])
            _path.push_back(v);

        reverse(_path.begin(), _path.end());
        return _path;
    }
};

// tested on problems: https://cses.fi/problemset/task/1671,
//                     https://www.spoj.com/problems/EZDIJKST/en/,
//                     https://judge.yosupo.jp/problem/shortest_path,
int main() {
    int T = 1;
    cin >> T;

    while (T-- > 0) {
        int N, M;
        cin >> N >> M;
        dijkstra<int64_t> graph(N);

        for (int i = 0; i < M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            graph.add_directed_edge(u, v, w);
        }

        int start, end;
        cin >> start >> end;
        start--, end--;
        graph.run_dijkstra(start);

        if (graph.distance(end) == INF) {
            cout << "NO\n";
        } else {
            cout << graph.distance(end) << '\n';
        }
    }

    return 0;
}
