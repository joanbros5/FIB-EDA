#include <iostream>
#include <vector>
using namespace std;

//Recursió
int inv(int e, int d, const vector<int>& v) {
    //Cas base, no queden elements
    int n = d - e + 1;
    if (e >= d or n <= 1) return 0;
    
    //Calcular el mig i cridar "mergesort"
    int m = (e + d) / 2;
    int res = inv(e, m, v) + inv(m+1, d, v);
    
    vector<int> B(n);
    int i = e;
    int j = m + 1;
    int k = 0;
    
    while (i <= m and j <= d) {
        if (v[i] <= v[j]) B[k++] = v[i++];
        else {
            B[k++] = v[j++];
            res += m - i + 1;
        }
    }
    
    //Acabar d'omplir el vector buffer
    while (i <= m) B[k++] = v[i++];
    while (j <= d) B[k++] = v[j++];
    
    for (int a = 0; a < n; ++a) B[a] = v[e+a];
    return res;
}

//MAIN
int main() {
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        cout << inv(0, v.size() - 1, v) << endl;
    }
}
