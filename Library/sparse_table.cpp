#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename table_t>struct sparse_table {
    int N, LOG;
    vector<table_t> A;
    vector<vector<table_t>> T;

    sparse_table(const vector<table_t> &_A) : A(_A) {
        assert(!_A.empty());
        init();
        build();
    }

    void init() {
        N = int(A.size());
        LOG = 32 - __builtin_clz(N);
        T.assign(N, vector<table_t>(LOG));
    }

    void build() {
        for (int i = 0; i < N; i++)
            T[i][0] = A[i];

        for (int k = 1; k < LOG; k++)
            for (int i = 0; i + (1 << k) <= N; i++)
                T[i][k] = operation(i, i + (1 << (k - 1)), k - 1);
    }

    table_t operation(int i, int j, int k) {
        if (T[i][k] <= T[j][k])
            return T[i][k];
        return T[j][k];
    }

    table_t query(int l, int r) {
        assert(0 <= l && l <= r && r < N);
        int msb = get_msb(r - l + 1);
        return operation(l, r - (1 << msb) + 1, msb);
    }

    int get_msb(int len) {
        assert(len > 0);
        return 31 - __builtin_clz(len);
    }
};

// tested on problems: https://judge.yosupo.jp/problem/staticrmq,
int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);

    for (auto &a : A)
        cin >> a;

    sparse_table<int> ST(A);

    for (int q = 0; q < Q; q++) {
        int l, r;
        cin >> l >> r;
        cout << ST.query(l, r - 1) << '\n';
    }

    return 0;
}
