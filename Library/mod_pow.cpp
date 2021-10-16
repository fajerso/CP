#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

unsigned mod_pow(unsigned b, unsigned e, unsigned mod) {
    unsigned result = 1;

    while (e > 0) {
        if (e & 1)
            result = uint64_t(result) * b % mod;

        b = uint64_t(b) * b % mod;
        e >>= 1;
    }

    return result;
}

unsigned mod_inv(unsigned a, unsigned mod) {
    return mod_pow(a, mod - 2, mod);
}

int main() {
    const int MOD = int(1e9) + 7;
    int N = 1e7;
    vector<int> fact(N + 1);
    vector<int> ifact(N + 1);
    fact[0] = ifact[0] = 1;

    for (int i = 1; i <= N; i++) {
        fact[i] = int64_t(fact[i - 1]) * i % MOD;
        ifact[i] = mod_inv(fact[i], MOD);
    }

    for (int i = 0; i <= N; i++)
        assert(int64_t(fact[i]) * ifact[i] % MOD == 1);

    return 0;
}
