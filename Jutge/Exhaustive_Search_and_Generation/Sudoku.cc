#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using VVE = vector<VE>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VVVB = vector<VVB>;

int n;
VVE S(9, VE(9,0));
VVB fila;
VVB col;
VVVB quad;


bool f(int i, int j) {
    //Has arribat a la fila ultima
    if (i == 9) {
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) cout << (y ? " " : "") << S[x][y];
            cout << endl;
        }
        return true;
    }
    
    //Has arribat a la columna ultima
    if (j == 9) {
        return f(i + 1, 0);
    }
    
    //Ja hi ha un numero posat
    if (S[i][j] != 0) {
        return f(i, j+1);
    }
    
    //Cas de posar un numero
    for (int x = 1; x <= 9; ++x) {
        if (not fila[i][x] and not col[j][x] and not quad[i/3][j/3][x]){
            S[i][j] = x;
            fila[i][x] = col[j][x] = true;
            quad[i/3][j/3][x] = true;
            if (f(i, j+1)) return true;
            S[i][j] = 0;
            fila[i][x] = col[j][x] = false;
            quad[i/3][j/3][x] = false;
        }
    }
    
    return false;
    
    
}

int main() {
    int t;
    cin >> t;
    cout << t << endl;
    while (t--) {
        fila = col = VVB(9, VB(10, false));
        quad = VVVB(3, VVB(3, VB(10, false)));
        for (int i = 0; i < 9; ++i){
            for (int j = 0; j < 9; ++j) {
                char c;
                cin >> c;
                if (c == '.') S[i][j] = 0;
                else {
                    int x = c - '0';
                    S[i][j] = x;
                    fila[i][x] = col[j][x] = quad[i/3][j/3][x] = true;
                }
            }
        }
        cout << endl;
        f(0, 0);
    }
}
