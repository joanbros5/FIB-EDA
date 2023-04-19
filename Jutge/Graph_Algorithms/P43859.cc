#include <iostream>
#include <vector>
#include <queue>
using namespace std;






            //CÓDIGO INACABADO Y MAL







void sol(int x, int y, vector<queue<pair<int,int>>> &G) {
    int d;
    bool OleOle = false;
    queue<pair<int,int>> q;
    
    //Primeras iteraciones para pillar los primeros vecinos
    while (not G[x].empty()) {
        q.push(make_pair(G[x].front().first, G[x].front().second));
        G[x].pop();
    }
    
    //Ahora en q tenemos a los vecinos de x con sus distancias y en d la distancia al primer vecino
    while (not q.empty()) {
        
        //Pillamos los datos de un vertice
        int vert1 = q.front().first;
        int caminito = q.front().second;
        
        q.pop();
        
        //Si es el destino OLEOLE
        if (vert1 == y) OleOle = true;
        
        
        
                    //EN EL SIGUIENTE WHILE FALTAN COSAS, HASTA AQUÍ TODO ESTÁ BIEN
        
        
        
        //Añade a la cola sus vecinos con la distancia modificada
        while (not G[vert1].empty()) {
            q.push(make_pair(G[vert1].front().first, G[G[vert1].front().first].front().second + caminito));
        }
        
        
        
        
    }
    
    if (OleOle) cout << d << endl;
    else cout << "no path from " << x << "to " << y << endl;
}

int main() {
    
    //Vertexs, arcs
    int n,m;
    while (cin >> n >> m) {
        
        vector<queue<pair<int,int>>> G(n);
        
        //Vertex 1, Vertex 2, coste de v1->v2
        int u, v, c;
        
        //Leer grafo
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> c;
            G[u].push(make_pair(v,c));
        }
        
        //De donde a donde hay que llegar
        int x,y;
        cin >> x >> y;
        
        sol(x,y, G);
    }
}
