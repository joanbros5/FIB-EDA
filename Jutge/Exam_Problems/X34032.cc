#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using Pos = pair<int,int>;
using VE = vector<int>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VC = vector<char>;
using VVC = vector<VC>;

int f,c, pasos;
bool trobat;
VVC tauler;

//Vectores para calcular los saltos: Clockwise
const VE inc_x = {1,2,2,1,-1,-2,-2,-1};
const VE inc_y = {2,1,-1,-2,-2,-1,1,2};

//Funció per escriure el tauler, DEBUG
void escriu_tauler() {
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < c; ++j) cout << tauler[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

//Funcion para determinar si una posición es válida para saltar
bool valid(int x, int y) {
    return x >= 0 and x < c and y >= 0 and y < f and tauler[y][x] != 'X';
}

//BFS per buscar pastanaga
void busca_pastanaga(int x, int y) {
    
    //El cavall comença en una pastanaga
    if (tauler[y][x] == 'p') {
        trobat = true;
        return;
    }
    
    //Marca casella com a visitada
    tauler[y][x] = 'X';
    
    //Queue de pair<Posició en el tauler, distancia en salta>
    queue<pair<Pos,int>> Q;                                         //Por algún motivo en el segundo ejemplo la cola está vacía
    
    //Primera iteració
    //Afegeix a la cua els veins on el cavall pot saltar
    for (int dir = 0; dir < 8; ++dir){
        Pos vecino = {x+inc_x[dir],y+inc_y[dir]};
        if (valid(vecino.first, vecino.second))
            Q.push(make_pair(vecino, 1));
    }
    
    //Iteracions del BFS
    while (not Q.empty() and not trobat) {
        Pos p = Q.front().first;
        pasos = Q.front().second;
        Q.pop();
        
        //Ha arribat a la pastanaga
        if (tauler[p.second][p.first] == 'p') {
            trobat = true;
            return;
        }
        
        //Marca casella com a visitada
        tauler[p.second][p.first] = 'X';
        
        //Següent iteració
        for (int dir = 0; dir < 8; ++dir){
            Pos vecino = {x+inc_x[dir],y+inc_y[dir]};
            if (valid(vecino.first, vecino.second)) Q.push(make_pair(vecino, pasos+1));
        }
        
    }
}

int main() {
    while(cin >> f >> c){
        int x,y;
        pasos = 0;
        trobat = false;
        tauler = VVC(f,VC(c));
        for (int i = 0; i < f; ++i) {
            for (int j = 0; j < c; ++j) cin >> tauler[i][j];
        }
        
        cin >> x >> y;
        
        busca_pastanaga(x-1,y-1);
        
        if (trobat) cout << pasos << endl;
        else cout << "no" << endl;
    }
}
