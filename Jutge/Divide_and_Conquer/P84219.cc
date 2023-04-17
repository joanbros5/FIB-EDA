#include <iostream>
#include <vector>
using namespace std;

int first_occurrence(double x, const vector<double>& v, int esq, int dre){
    if (esq > dre) return -1;                        // x No està en el vector
    int m = (dre + esq) / 2;
    
    if (x < v[m]) return first_occurrence(x,v,esq,m-1);
    else if (x > v[m]) return first_occurrence(x,v,m+1,dre);
    else {
        if (m-1 >= esq and v[m-1] == x) return first_occurrence(x,v,esq,m-1);
        else return m;
    }
}

int first_occurrence(double x, const vector<double>& v){
    return first_occurrence(x,v,0,v.size()-1);
}

int main() {
    int n;
    cin >> n;
    double x;
    
    vector<double> v(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    cin >> x;
    cout << endl;
    cout << "L'element " << x << " està en la posició " << first_occurrence(x,v) << endl;
    
    
}
