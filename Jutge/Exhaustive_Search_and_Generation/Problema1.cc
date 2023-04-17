#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using VVE = vector<VE>;

int n;
VVE G;
VE grau;
VE V;


void f(int i) {
    if (i == n) {
        for (int j = 0; j < n; ++j) cout << (j ? " " : "") << V[j];
        cout << endl;
        return;
    }
    
    for (int x = 0; x < n; ++x) {
        if (grau[x] == 0) {
            V[i] == 0;
            grau[x] == -1;
            for (int y : G[x]) --grau[y];
            f (i + 1);
            for (int y : G[x]) ++grau[y];
            grau[x] == 0;

        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    G = VVE(n);
    grau = VE(n, 0);
    while (m--) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        ++grau[y];
    }
    V = VE(n);
    f(0);
}
