#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    int T = 6;
    int64_t MAX = int64_t(1e12) + 5;
    cout << T << endl;

    while (T--) {
        int64_t A = 1 + int64_t(rand()) * int64_t(rand()) % MAX;
        cout << A << '\n';
    }

    return 0;
}
