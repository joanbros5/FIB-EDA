#include <iostream>
#include <vector>
using namespace std;

bool posicio(double x, const vector<double>& v, int esq, int dre){
    if (esq > dre) return false;                        // x No està en el vector
    int m = (dre + esq) / 2;
    
    double y = v[m];
    if (m - 1 > 0 and v[m-1] > y) y = v[m-1];
    if (m + 1 < int(v.size()) and v[m+1] > y) y = v[m+1];
    
    
    if (x < v[m]) return posicio(x,v,esq,m-1);
    else if (x > v[m]) return posicio(x,v,m+1,dre);
    else return true;
}


bool resistant_search(double x, const vector<double>& v){
    return posicio(x,v, 0, v.size()-1);
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
