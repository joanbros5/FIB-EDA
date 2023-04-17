#include <iostream>
#include <vector>
using namespace std;

int fixedpoint(vector<int>& v, int a, int esq, int dre) {
    if (esq > dre) return -1;
    else {
        int m = (esq+dre)/2;
        if (v[m] + a < m) return fixedpoint(v,a,m+1,dre);
        else if (v[m] + a < m) return fixedpoint(v,a,esq,m-1);
        else {
            if (m-1 >= esq and v[m-1] + a == m-1) return fixedpoint(v,a,esq,m-1);
            else return m;
        }
    }
}

int fixedpoint(vector<int>& v, int a) {
    return fixedpoint(v,a,1,v.size()-1);
}

int main() {
    int NumSeq = 1;
    int n;
    int NumFixPoints;
    int a;
    
    while (cin >> n) {
        cout << "Sequence #" << NumSeq << endl;
        
        vector<int> v(n+1);
        for (int i = 1; i <= n; ++i) cin >> v[i];
        
        cin >> NumFixPoints;
        
        for (int j = 0; j < NumFixPoints; ++j) {
            cin >> a;
            int p = fixedpoint(v,a);
            if (p == -1) cout << "no fixed point for " << a << endl;
            else cout << "fixed point for " << a << ": " << p << endl;
        }
        
        cout << endl;
        ++NumSeq;
    }
}
