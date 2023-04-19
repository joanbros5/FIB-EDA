#include <iostream>
#include <vector>
using namespace std;

using VC = vector<char>;
using VB = vector<bool>;

VC solucio;
VC consonants;
VC vocals;
VB usatV;
VB usatC;
int n;

void sol(int x) {
    
    //DEBUG
    //cout << "Estoy en sol " << x << endl;
    
    //Hem arribat al final, escriu el vector
    if (x == 2*n) {
        for (int j = 0; j < 2*n; ++j) cout << solucio[j];
        cout << endl;
        return;
    }
    
    //En les x impars estem fent vocals
    if (x % 2) {
        for (int v = 0; v < n; ++v) {
            if (not usatV[v]) {
                
                //DEBUG
                //cout << "Pruebo la " << vocals[v] << endl;
                
                solucio[x] = vocals[v];
                usatV[v] = true;
                sol(x + 1);
                usatV[v] = false;
            }
        }
    }
    
    //En les x pars estem en consonants
    else {
        for (int c = 0; c < n; ++c) {
            if (not usatC[c]) {
                
                //DEBUG
                //cout << "Pruebo la " << consonants[c] << endl;
                
                solucio[x] = consonants[c];
                usatC[c] = true;
                sol(x + 1);
                usatC[c] = false;
            }
        }
    }
    
}

int main() {
    while (cin >> n) {
        consonants = VC(n);
        usatC = VB(n, false);
        for (int i = 0; i < n; ++i) cin >> consonants[i];
        vocals = VC(n);
        usatV = VB(n, false);
        for (int i = 0; i < n; ++i) cin >> vocals[i];
        
        solucio = VC(2*n);
        
        sol(0);
    }
}
