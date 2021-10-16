#include <bits/stdc++.h>
using namespace std;

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef TUAN_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename tree_t>struct lazy_seg_tree {
    struct node {
        tree_t sum, val, add;
        bool assigned;
        int len;

        node(tree_t _init_val) : sum(_init_val), val(_init_val), add(_init_val), assigned(false), len(1) {}
        void reset() { add = 0; assigned = false; }

        void assign_val(tree_t _val) {
            assigned = true;
            val = _val;
            add = 0;
        }
    };

    int N;
    vector<tree_t> A;
    vector<node> tree;
    const tree_t init_val = 0;

    lazy_seg_tree(const vector<tree_t> &_A) : A(_A) {
        assert(!A.empty());
        init();
        build();
    }

    void init() {
        N = 1 << (31 - __builtin_clz(A.size()) + (__builtin_popcount(A.size()) > 1));
        tree.assign(2 * N, node(init_val));
    }

    void build() {
        for (int i = 0; i < int(A.size()); i++) {
            tree[i + N].sum = tree[i + N].val = A[i];
            tree[i + N].assigned = true;
        }

        for (int i = N - 1; i >= 1; i--)
            tree[i].sum = operation(tree[2 * i].sum, tree[2 * i + 1].sum);

        tree[1].len = N;

        for (int i = 1; i < N; i++)
            tree[2 * i].len = tree[2 * i + 1].len = tree[i].len / 2;
    }

    tree_t operation(const tree_t &l, const tree_t &r) const {
        return l + r;
    }

    tree_t node_sum(int v) {
        return (tree[v].assigned ? tree[v].len * tree[v].val : tree[v].sum) + tree[v].len * tree[v].add;
    }

    tree_t query(int l, int r) {
        assert(0 <= l && l <= r && r < int(A.size()));
        return _query(1, 0, N - 1, l, r);
    }

    tree_t _query(int v, int tl, int tr, int ql, int qr) {
        if (tr < ql || qr < tl)
            return init_val;

        if (ql <= tl && tr <= qr)
            return node_sum(v);

        push(v);
        int mid = tl + (tr - tl) / 2;
        tree_t res = operation(_query(2 * v, tl, mid, ql, qr), _query(2 * v + 1, mid + 1, tr, ql, qr));
        node_update(v);
        return res;
    }

    void push(int v) {
        if (tree[v].assigned) {
            tree[2 * v].assigned = tree[2 * v + 1].assigned = true;
            tree[2 * v].val = tree[2 * v + 1].val = tree[v].val;
            tree[2 * v].add = tree[2 * v + 1].add = tree[v].add;
            tree[v].reset();
        } else {
            tree[2 * v].add += tree[v].add;
            tree[2 * v + 1].add += tree[v].add;
            tree[v].reset();
        }
    }

    void node_update(int v) {
        tree[v].sum = operation(node_sum(2 * v), node_sum(2 * v + 1));
    }

    void range_assign(int l, int r, tree_t val) {
        _range_assign(1, 0, N - 1, l, r, val);
    }

    void _range_assign(int v, int tl, int tr, int ql, int qr, tree_t val) {
        if (tr < ql || qr < tl)
            return;

        if (ql <= tl && tr <= qr) {
            tree[v].assign_val(val);
            return;
        }

        push(v);
        int mid = tl + (tr - tl) / 2;
        _range_assign(2 * v, tl, mid, ql, qr, val);
        _range_assign(2 * v + 1, mid + 1, tr, ql, qr, val);
        node_update(v);
    }

    void range_add(int l, int r, tree_t val) {
        _range_add(1, 0, N - 1, l, r, val);
    }

    void _range_add(int v, int tl, int tr, int ql, int qr, tree_t val) {
        if (tr < ql || qr < tl)
            return;

        if (ql <= tl && tr <= qr) {
            tree[v].add += val;
            return;
        }

        push(v);
        int mid = tl + (tr - tl) / 2;
        _range_add(2 * v, tl, mid, ql, qr, val);
        _range_add(2 * v + 1, mid + 1, tr, ql, qr, val);
        node_update(v);
    }
};

// tested on problems: https://cses.fi/problemset/task/1735,
//
void run_case() {
    int N, Q;
    cin >> N >> Q;
    vector<int64_t> A(N);

    for (auto &a : A)
        cin >> a;

    lazy_seg_tree<int64_t> tree(A);

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            tree.range_add(l, r, val);
        } else if (t == 2) {
            int l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            tree.range_assign(l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << tree.query(l, r) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
#ifndef TUAN_DEBUG
    cin.tie(nullptr);
#endif

    int tests = 1;
    //cin >> tests;

    while (tests-- > 0) {
        run_case();
    }

    return 0;
} 
