#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename tree_t> struct seg_tree {
    int N;
    vector<tree_t> A;
    vector<tree_t> tree;
    const tree_t init_val = 0;

    seg_tree(const vector<tree_t> &_A) : A(_A) {
        assert(!A.empty());
        init();
        build();
    }

    void init() {
        N = 1 << (31 - __builtin_clz(A.size()) + (__builtin_popcount(A.size()) > 1));
        tree.assign(2 * N, init_val);
    }

    void build() {
        for (int i = 0; i < int(A.size()); i++)
            tree[i + N] = A[i];

        for (int i = N - 1; i >= 1; i--)
            tree[i] = operation(tree[2 * i], tree[2 * i + 1]);
    }

    tree_t operation(const tree_t &l, const tree_t &r) const {
        return l + r;
    }

    tree_t query(int l, int r) {
        assert(0 <= l && l <= r && r < int(A.size()));
        return _query(1, 0, N - 1, l, r);
    }

    tree_t _query(int v, int tl, int tr, int ql, int qr) {
        if (tr < ql || qr < tl)
            return init_val;

        if (ql <= tl && tr <= qr)
            return tree[v];

        int mid = tl + (tr - tl) / 2;
        return operation(_query(2 * v, tl, mid, ql, qr), _query(2 * v + 1, mid + 1, tr, ql, qr));
    }

    void change_val(int i, tree_t val) {
        assert(0 <= i && i < int(A.size()));
        _change_val(i, val);
    }

    void _change_val(int i, tree_t val) {
        i += N;
        tree[i] = val;

        for (i = i / 2; i > 0; i /= 2)
            tree[i] = operation(tree[2 * i], tree[2 * i + 1]);
    }
};

// tested on problems: https://cses.fi/problemset/task/1648,
//                     https://judge.yosupo.jp/problem/static_range_sum,
int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int64_t> A(N);

    for (auto &a : A)
        cin >> a;

    seg_tree<int64_t> tree(A);

    for (int q = 0; q < Q; q++) {
        int t;
        cin >> t;

        if (t == 1) {
            int id, val;
            cin >> id >> val;
            tree.change_val(id - 1, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tree.query(l - 1, r - 1) << '\n';
        }
    }

    return 0;
}
