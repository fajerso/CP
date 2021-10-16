#include <iostream>
#include <cassert>
using namespace std;

int ext_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }

    int x1, y1;
    int g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

int main() {
    int T;
    cin >> T;

    while (T-- > 0) {
        int A, B;
        cin >> A >> B;
        int x, y;
        int G = ext_gcd(A, B, x, y);
        if (A % G != 0 || B % G != 0)
            cerr << "A = " << A << ", B = " << B << ", GCD: " << G << endl;
        else if (A * x + B * y != G)
            cerr << "A = " << A << ", B = " << B << ", GCD: " << G << endl;
    }

    return 0;
}
