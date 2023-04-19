#include <iostream>
#include <vector>
#include <stack>
using namespace std;

using VC = vector<char>;
using VVC = vector<VC>;
using VE = vector<int>;

int n,m;
VVC Mapa;
bool trobat = false;

const VE inc_x = {0, 0, -1, 1};
const VE inc_y = {1, -1, 0, 0};

bool casilla_posible(int x, int y, const vector<vector<char>>& Mapa) {
	return x >= 0 and y >= 0 and x < n and y < m and Mapa[x][y] != 'X';
}

void sol(int x, int y) {
	
	//He llegado a un tesoro
	if (Mapa[x][y] == 't') {
		trobat = true;
		return;
	}

	Mapa[x][y] = 'X';

	if (not trobat){
		for (int dir = 0; dir < 4; ++dir) {
			if (casilla_posible(x + inc_x[dir], y + inc_y[dir], Mapa))
			sol(x + inc_x[dir], y + inc_y[dir]);
		}
	}
}

int main() {
    cin >> n >> m;
    Mapa = VVC(n, VC(m));
    for (int i = 0; i < n; ++i) {
        for ( int j = 0; j < m; ++j) cin >> Mapa[i][j];
    }
    int x,y;
    cin >> x >> y;
    
    sol(x-1, y-1);
    cout << (trobat ? "yes" : "no") << endl;
}
