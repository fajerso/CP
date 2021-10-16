#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
using namespace std;

struct DSU {
    int N;
    vector<int> parent;
    vector<int> component_size;

    DSU(int _N) : N(_N) {
        init();
    }

    void init() {
        parent.resize(N);
        component_size.assign(N, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int a) {
        return parent[a] == a ? a : parent[a] = find(parent[a]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (component_size[a] < component_size[b])
            swap(a, b);

        parent[b] = a;
        component_size[a] += component_size[b];
        return true;
    }
};

// tested on problems: https://atcoder.jp/contests/abc206/tasks/abc206_d,
//                     https://judge.yosupo.jp/problem/unionfind,
int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    DSU dsu(int(2e5));

    for (auto &a : A)
        cin >> a;

    int ops = 0;

    for (int i = 0; i < N / 2; i++)
        ops += dsu.unite(A[i] - 1, A[N - 1 - i] - 1);

    cout << ops << '\n';
}
