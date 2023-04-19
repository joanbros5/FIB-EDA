#include <iostream>
#include <vector>
#include <stack>
using namespace std;

using VC = vector<char>;
using VVC = vector<VC>;
using VE = vector<int>;

int n,m;
VVC Mapa;
int resultat = 0;

const VE inc_x = {0, 0, -1, 1};
const VE inc_y = {1, -1, 0, 0};

bool casilla_valida(int x, int y) {
    return x >= 0 and x < n and y >= 0 and y < m and Mapa[x][y] != 'X';
}

void sol(int x, int y) {
    if (Mapa[x][y] == 't') ++resultat;
    
    Mapa[x][y] = 'X';
    
    for (int dir = 0; dir < 4; ++dir) {
        if (casilla_valida(x+inc_x[dir], y+inc_y[dir]))
            sol(x+inc_x[dir],y+inc_y[dir]);
    }
}

int main() {
    
    //Lectura del mapa
    cin >> n >> m;
    Mapa = VVC(n,VC(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> Mapa[i][j];
    }
    
    //Coordenades inicials
    int x,y;
    cin >> x >> y;
    
    sol(x-1,y-1);
    
    cout << resultat << endl;
}
