#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector<int> phi;

int get_phi(int n) {
    int result = n;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            do {
                n /= i;
            } while (n % i == 0);

            result -= result / i;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
}

void phi_till_n(int n) {
    phi.assign(n + 1, 0);
    iota(phi.begin(), phi.end(), 0);

    for (int i = 2; i <= n; i++)
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
}


int main() {

    return 0;
}
