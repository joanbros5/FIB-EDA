#include <iostream>
#include <vector>
#include <stack>
using namespace std;

using VC = vector<char>;
using VVC = vector<VC>;
using VE = vector<int>;
using VB = vector<bool>;
using VVB = vector<VB>;

int n,m;
int cont;
bool sepuede;
VVC Mapa;
VVB visitado;

const VE inc_x = {1, 1, -1, -1};
const VE inc_y = {1, -1, -1, 1};

//Funcion para determinar si una casilla es válida
bool casilla_valida(int x, int y) {
    return x >= 0 and x < n and y >= 0 and y < m and Mapa[x][y] != 'X' and (not visitado[x][y]);
}

void recursion_cc(int x, int y, int bishops) {
    
    //No funciona si los números son de más de 1 dígito
    bishops += Mapa[x][y] - '0';
    
    //Faltan hacer cosas de DFS
}

//Funcion que calcula el resultado de los bishops de un Component Connex
int res_cc(int x, int y) {

    int bishops = 0;
    
    recursion_cc(x, y, bishops);
    
    if (bishops % casillas) sepuede = false;
    else cont = bishops / casillas;
    
    return cont;
}

void sol(int x, int y) {
    
    //Faltan cosas de comparar resultados de los cc
    
}

int main() {
    
    //Numero de casos
    cin >> cont;
    for (int i = 1; i <= cont; ++i) {
        
        //Inicializar variables
        sepuede = true;
        cin >> n >> m;
        Mapa = VVC(n, VC(m));
        visitado = VVB(n, VB(m, false));
        for (int pito = 0; pito < n; ++pito) {
            for (int pita = 0; pita < m; ++pita)
                cin >> Mapa[pito][pita];
        }
        
        //Calcular bishops
        for (int x = 0; x < n and not sepuede; ++x) {
            for (int y = 0; y < m and not sepuede; ++y)
                if (casilla_valida(x,y)) sol(x,y);
        }
        
        cout << "Case " << i << ": " << (sepuede ? "yes" : "no") << endl;
        
    }
}
