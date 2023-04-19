#include <iostream>
using namespace std;

int eleva(int n, int k, int m) {
    if (k == 0) return 1;
    int res = eleva(n, k/2, m);
    res = (res*res) % m;
    if (k % 2) res = (res*n) % m;
    return res;
}

int main() {
    int n, k, m;
    while (cin >> n >> k >> m) cout << eleva(n, k, m) << endl;
}
