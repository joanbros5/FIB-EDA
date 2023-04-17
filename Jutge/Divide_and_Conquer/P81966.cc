#include <iostream>
#include <vector>
using namespace std;

int posicio(double x, const vector<double>& v, int esq, int dre){
    if (esq > dre) return -1;                        // x No està en el vector
    int m = (dre + esq) / 2;
    
    if (x < v[m]) return posicio(x,v,esq,m-1);
    else if (x > v[m]) return posicio(x,v,m+1,dre);
    else return m;
}

int main() {
    int n;
    cin >> n;
    int x;
    
    vector<double> v(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    cin >> x;
    cout << endl;
    cout << "L'element " << x << " està en la posició " << posicio(x,v,0,n-1) << endl;
    
    
}
