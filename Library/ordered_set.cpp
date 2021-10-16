#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// ordered_set supports these 2 operations: 1.) find by order(k) -> returns an iterator to the k-th largest element (starting from 0)
//                                          2.) order_of_key(x) -> the number of items strictly smaller than x
int main() {
    ordered_set S;
    S.insert(0); S.insert(1); S.insert(3);
    cout << S.order_of_key(3) << '\n';

    return 0;
}
