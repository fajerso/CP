#include<cassert>
#include<iostream>
#include<array>
using namespace std;

uint64_t mod_pow(uint64_t b, uint64_t e, uint64_t MOD) {
    uint64_t res = 1;

    while (e > 0) {
        if (e & 1)
            res = uint64_t(__uint128_t(res) * b % MOD);

        b = uint64_t(__uint128_t(b) * b % MOD);
        e >>= 1;
    }

    return res;
}

bool miller_rabin(uint64_t n) {
    if (n < 2)
        return false;

    static const array<unsigned, 12> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (unsigned p : primes)
        if (n % p == 0)
            return n == p;

    int r = __builtin_ctzll(n - 1);
    unsigned d = (n - 1) >> r;

    for (unsigned a : primes) {
        uint64_t x = mod_pow(a % n, d, n);

        if (x <= 1 || x == n - 1)
            continue;

        for (int i = 0; i < r - 1 && x != n - 1; i++)
            x = uint64_t(__uint128_t(x) * x % n);

        if (x != n - 1)
            return false;
    }

    return true;
}

int main() {

    return 0;
}
