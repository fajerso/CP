#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

vector<bool> prime;
vector<int> primes;
vector<int> smallest_factor;

void sieve(int n) {
    smallest_factor.assign(n + 1, 1);
    prime.assign(n + 1, true);
    prime[0] = prime[1] = false;
    primes = {};

    for (int i = 2; i <= n; i++) {
        if (prime[i]) {
            primes.push_back(i);
            smallest_factor[i] = i;

        for (int64_t j = int64_t(i) * i; j <= n; j += i)
            if (prime[j]) {
                prime[j] = false;
                smallest_factor[j] = i;
            }
        }
    }
}

vector<pair<int64_t, int>> prime_factorize(int64_t n) {
    int sieve_max = int(smallest_factor.size()) - 1;
    assert(1 <= n && n <= int64_t(sieve_max) * sieve_max);
    vector<pair<int64_t, int>> result;

    if (n <= sieve_max) {
        while (n != 1) {
            int count = 0;
            int p = smallest_factor[n];

            do {
                n /= p;
                count++;
            } while (smallest_factor[n] == p);

            result.emplace_back(p, count);
        }

        return result;
    }

    for (int p : primes) {
        if (int64_t(p) * p > n)
            break;

        if (n % p == 0) {
            result.emplace_back(p, 0);

            do {
                n /= p;
                result.back().second++;
            } while (n % p == 0);
        }
    }

    if (n > 1)
        result.emplace_back(n, 1);

    return result;
}


int main() {
    sieve(int(1e8));

    int T;
    cin >> T;

    while (T-- > 0) {
        int64_t N;
        cin >> N;
        vector<pair<int64_t, int>> P = prime_factorize(N);

        cout << N << ": ";
        for (auto &pf : P)
            cout << ' ' << pf.first << ' ' << pf.second << "  ";
        cout << endl;
    }

    return 0;
}
