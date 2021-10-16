#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<int _MOD> struct mod_int {
    static constexpr int MOD = _MOD;
    static_assert(MOD > 0, "MOD must be positive!!!");

    int v;

    mod_int() : v(0) {}
    mod_int(int64_t _v) : v(int(_v % MOD)) { if (v < 0) v += MOD; }

    explicit operator int() const { return v; }
    explicit operator unsigned() const { return v; }
    explicit operator int64_t() const { return v; }
    explicit operator uint64_t() const { return v; }
    explicit operator double() const { return v; }
    explicit operator long double() const { return v; }

    mod_int& operator += (const mod_int &other) {
        v -= MOD - other.v;
        if (v < 0) v += MOD;
        return *this;
    }

    mod_int& operator -= (const mod_int &other) {
        v -= other.v;
        if (v < 0) v += MOD;
        return *this;
    }

    mod_int& operator *= (const mod_int &other) {
        v = int(uint64_t(v) * other.v % MOD);
        return *this;
    }

    friend mod_int _pow(mod_int b, int64_t e) {
        mod_int res = 1;
        while (e > 0) { if (e & 1) res *= b; b *= b; e >>= 1; }
        return res;
    }

    mod_int _inv(mod_int a) { return _pow(a, MOD - 2); }

    mod_int& operator /= (const mod_int &other) {
        return *this *= _inv(other.v);
    }

    friend mod_int operator + (const mod_int &a, const mod_int &b) { return mod_int(a) += b; }
    friend mod_int operator - (const mod_int &a, const mod_int &b) { return mod_int(a) -= b; }
    friend mod_int operator * (const mod_int &a, const mod_int &b) { return mod_int(a) *= b; }
    friend mod_int operator / (const mod_int &a, const mod_int &b) { return mod_int(a) /= b; }

    mod_int& operator ++ () {
        v = v == MOD - 1 ? 0 : v + 1;
        return *this;
    }

    mod_int& operator -- () {
        v = v == 0 ? MOD - 1 : v - 1;
        return *this;
    }

    mod_int operator ++ (int) {
        mod_int before = *this; ++*this;
        return before;
    }

    mod_int operator -- (int) {
        mod_int before = *this; --*this;
        return before;
    }

    mod_int operator - () const {
        return v == 0 ? 0 : MOD - v;
    }

    friend std::ostream& operator << (std::ostream &out, const mod_int &a) { return out << a.v; }
    friend std::istream& operator >> (std::istream &in, mod_int &a) { return in >> a.v; }

    friend bool operator == (const mod_int &a, const mod_int &b) { return a.v == b.v; }
    friend bool operator != (const mod_int &a, const mod_int &b) { return a.v != b.v; }
    friend bool operator < (const mod_int &a, const mod_int &b) { return a.v < b.v; }
    friend bool operator > (const mod_int &a, const mod_int &b) { return a.v > b.v; }
    friend bool operator <= (const mod_int &a, const mod_int &b) { return a.v <= b.v; }
    friend bool operator >= (const mod_int &a, const mod_int &b) { return a.v >= b.v; }
};

const int MOD = int(1e9) + 7;
using mint = mod_int<MOD>;
vector<mint> _fact = {1, 1}, _inv_fact = {1, 1};

void prepare_fact(int n) {
    static int prepared_max = 1;

    if (n <= prepared_max)
        return;

    _fact.resize(n + 1);
    _inv_fact.resize(n + 1);

    for (int i = prepared_max + 1; i <= n; i++) {
        _fact[i] = _fact[i - 1] * i;
        _inv_fact[i] = _inv_fact[i - 1] / i;
    }

    prepared_max = int(n);
}

mint fact(int n) {
    if (n < 0) return 0;
    prepare_fact(n);
    return _fact[n];
}

mint inv_fact(int n) {
    if (n < 0) return 0;
    prepare_fact(n);
    return _inv_fact[n];
}

mint C(int n, int k) {
    if (k < 0 || k > n) return 0;
    prepare_fact(n);
    return _fact[n] * _inv_fact[k] * _inv_fact[n - k];
}

mint V(int n, int k) {
    if (k < 0 || k > n) return 0;
    prepare_fact(n);
    return _fact[n] * _inv_fact[n - k];
}

mint inv_C(int n, int k) {
    assert(0 <= k && k <= n);
    prepare_fact(n);
    return _fact[k] * _fact[n - k] * _inv_fact[n];
}

mint inv_V(int n, int k) {
    assert(0 <= k && k <= n);
    prepare_fact(n);
    return _fact[n - k] * _inv_fact[n];
}

int main() {
    mint A = int(1e9) + 20000;
    mint B = int64_t(500);
    cout << A << ' ' << B << '\n';

    return 0;
}
