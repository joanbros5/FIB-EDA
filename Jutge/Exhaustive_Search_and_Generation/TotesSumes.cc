#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;

int suma;
int n;
VE V;
VB usat;

void f(int i, int s) {
    if (i == n) {
        if (s != suma) return;
        bool primer = true;
        cout << '{';
        for (int j = 0; j < n; ++j) {
            if (usat[j]){ 
                if (primer) primer = false;
                else cout << ' ';
                cout << V[j];
            }
        }
        cout << endl;
        return;
    }
    
    usat[i] = false;
    f(i+1, s);
    usat[i] = true;
    f(i+1, s + V[i]);
}

int main() {
    cin >> s >> n;
    num = VE(n);
    for (int i = 0; i < n; ++i) cin >> num[i];
    usat = VB(n, false);    
    f(0, 0);
    
}
