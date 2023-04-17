#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Joandalf_v3


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

                                //Joandalf_v3   -   copiado desde Joandalf_v2
                                //GANA 75-80% CONTRA DUMMYS, gana a Joandalf y Joandalf_v2
                                
                                //Changelog:    No hay grupos, todos los dwarfs hacen lo mismo
                                //              Prio:   pegarse si mago / peligro > tesoro si está cerca > conquer random
                                //              DFS a tesoros hecho con matriz de visitados para mejor eficiencia en CPU   
                                //                      
                                //              
  
  
  /**
   * Types and attributes for your player can be defined here.
   */
  
    using VB = vector<bool>;
    using VVB = vector<VB>;
    using VE = vector<int>;
    using VVE = vector<VE>;
    
    //Typedef para el Dijkstra
    typedef pair<int, pair<Pos, Dir>> dijkstra;
    
    //Matriz de visitado para los dfs
    VVB visitado;
    
    //Vector random para hacer cosas
    VE randomV;
    int decision;
    
    //Bool para determinar si una unidad es kamikaze                    UNUSED En este game
    //bool kamikaze;
    
    //Vectores con direcciones por defecto (Con diagonales y sin diagonales)
    const vector<Dir> direc_D = {Bottom, Right, Top, Left, BR, RT, TL, LB};
    const vector<Dir> direc = {Top, Right, Bottom, Left};
    
    //Función que devuelve una dirección completamente opuesta a dir
    Dir opposite(Dir dir) {
        if (dir == Bottom) return Top;
        else if (dir == BR) return TL;
        else if (dir == Right) return Left;
        else if (dir == RT) return LB;
        else if (dir == Top) return Bottom;
        else if (dir == TL) return BR;
        else if (dir == Left) return Right;
        else if (dir == LB) return RT;
        else return None;
    }
    
    //DFS para saber si hay un enemigo en un radio x (con diagonales)
    bool enemigo_cerca_D(Pos actual, int x) {
        if (not pos_ok(actual)) return false;
        if (x < 0) return false;
        else {
          Cell cuadrado = cell(actual);
          if (cuadrado.id != -1) {
            Unit alguien = unit(cuadrado.id);
            if (alguien.player != me()) return true;
          }
          return enemigo_cerca_D(actual + Bottom, x-1) or enemigo_cerca_D(actual + BR, x-1) or
          enemigo_cerca_D(actual + Right, x-1) or enemigo_cerca_D(actual + RT, x-1) or 
          enemigo_cerca_D(actual + Top, x-1) or enemigo_cerca_D(actual + TL, x-1) or 
          enemigo_cerca_D(actual + Left, x-1) or enemigo_cerca_D(actual + LB, x-1);
      }
    }
    
    
    //DFS para saber si hay un enemigo en un radio x (sin diagonales)
    bool enemigo_cerca_ND(Pos actual, int x) {
        if (not pos_ok(actual)) return false;
        if (x < 0) return false;
        else {
          Cell cuadrado = cell(actual);
          if (cuadrado.id != -1) {
            Unit alguien = unit(cuadrado.id);
            if (alguien.player != me()) return true;
          }
          return enemigo_cerca_ND(actual + Bottom, x-1) or
          enemigo_cerca_ND(actual + Right, x-1) or 
          enemigo_cerca_ND(actual + Top, x-1) or 
          enemigo_cerca_ND(actual + Left, x-1);
      }
    }
    
    //DFS para saber si hay un mago aliado en un radio x (sin diagonales)
    bool mago_cerca(Pos actual, int x) {
        if (not pos_ok(actual)) return false;
        if (x < 0) return false;
        else {
          Cell cuadrado = cell(actual);
          if (cuadrado.id != -1) {
            Unit alguien = unit(cuadrado.id);
            if (alguien.type == Wizard and alguien.player == me()) return true;
          }
          return mago_cerca(actual + Bottom, x-1) or
          mago_cerca(actual + Right, x-1) or 
          mago_cerca(actual + Top, x-1) or 
          mago_cerca(actual + Left, x-1);
      }
    }
    
    //DFS para saber si hay un tesoro en un radio x (con diagonales) (detecta si hay obstáculos de por medio)
    bool tesoro_cerca_D(Pos actual, int x, VVB& visitado) {
        if (x < 0) return false;
        if (not pos_ok(actual) or visitado[actual.i][actual.j] or cell(actual).type == Granite or cell(actual).type == Abyss) return false;
        else {
          Cell cuadrado = cell(actual);
          visitado[actual.i][actual.j] = true;
          if (cuadrado.treasure) return true;
          return tesoro_cerca_D(actual + Bottom, x-1, visitado) or tesoro_cerca_D(actual + BR, x-1, visitado) or
          tesoro_cerca_D(actual + Right, x-1, visitado) or tesoro_cerca_D(actual + RT, x-1, visitado) or 
          tesoro_cerca_D(actual + Top, x-1, visitado) or tesoro_cerca_D(actual + TL, x-1, visitado) or 
          tesoro_cerca_D(actual + Left, x-1, visitado) or tesoro_cerca_D(actual + LB, x-1, visitado);
      }
    }
    
    //BFS para llegar a un tesoro (con diagonales) // Cueva = 1 casilla, piedra = 5 casillas
    Dir bfs_tesoro(Pos actual, VVB Ocupat) {
        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales con diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] or [es roca] and [no hay nadie] and [no visitado] and [no ocupado]
        for (int count = 0; count < 8; ++count) {
          dirini = direc_D[count];
          Pos next = actual + direc_D[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside or cell(next).type == Rock) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                  Q.push(make_pair(next, direc_D[count]));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Tesoro encontrado
            if (cell(P).treasure and not Ocupat[P.i][P.j]) {
                return dirini;
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 8; ++count) {
                    Pos next = P + direc_D[count];
                    if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside or cell(next).type == Rock) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
        
        //No se puede llegar a un tesoro
        return None;
    }
    
    //DIJKSTRA para llegar a un tesoro (con diagonales) // Cueva = peso 1, piedra = peso 5
    Dir dk_tesoro(Pos actual, VVB Ocupat) {
        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        priority_queue<dijkstra, vector<dijkstra>, greater<dijkstra>> Q;
        Visitado[actual.i][actual.j] = true;
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales con diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] or [es roca] and [no hay nadie] and [no visitado] and [no ocupado]
        for (int count = 0; count < 8; ++count) {
          dirini = direc_D[count];
          Pos next = actual + direc_D[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside or cell(next).type == Rock) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                if (cell(next).type == Cave or cell(next).type == Outside){
                  Q.push(make_pair(1, make_pair(next, direc_D[count])));
                }
                else if (cell(next).type == Rock) Q.push(make_pair(2, make_pair(next, direc_D[count])));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            int dist = Q.top().first;
            Pos P = Q.top().second.first;
            dirini = Q.top().second.second;
            Q.pop();
            
            //Tesoro encontrado
            if (cell(P).treasure and not Ocupat[P.i][P.j] and pos_ok(P)) {
                
                //DEBUG
                //cerr << "He encontrado un tesoro" << endl;
                //cerr << "Dirini es " << dirini << endl;
                return dirini;
            }
            
            else if (not Visitado[P.i][P.j]) {
                
                //DEBUG
                //cerr << "Meto la posicion " << P.i << " " << P.j << endl;
                
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 8; ++count) {
                    Pos next = P + direc_D[count];
                    if (pos_ok(next) and (cell(next).type == Cave or cell(next).type == Outside or cell(next).type == Rock) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j])) {
                        if (cell(next).type == Cave or cell(next).type == Outside){
                            Q.push(make_pair(dist + 1, make_pair(next, direc_D[count])));
                        }
                        else if (cell(next).type == Rock) Q.push(make_pair(dist + 2, make_pair(next, direc_D[count])));
                    }
                }
            }
        }
        
        //No se puede llegar a un tesoro
        return None;
    }
    
    //BFS para llegar al lado de un dwarf (para los magos), sin diagonales
    Dir bfs_dwarf(Pos actual, VVB Ocupat) {
        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales sin diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] and [no visitado] and [no ocupado]
        for (int count = 0; count < 4; ++count) {
          dirini = direc[count];
          Pos next = actual + direc[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                  Q.push(make_pair(next, direc[count]));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Dwarf aliado encontrado
            if (cell(P).id != -1){
                if (unit(cell(P).id).player == me() and unit(cell(P).id).type == Dwarf) {
                    return dirini;
                }
            
            }
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 4; ++count) {
                    Pos next = P + direc[count];
                    if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
        
        //No hay amigos cerca :(
        return None;
    }
    
    //BFS para ir hacia cuevas neutrales, con diagonales
    Dir bfs_conquer_neutral(Pos actual, VVB Ocupat) {
        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        
        //Vector random para más eficiencia en el bfs
        randomV = random_permutation(8);
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales sin diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] and [no hay nadie] and [no visitado] and [no ocupado]
        for (int count = 0; count < 8; ++count) {
          dirini = direc_D[randomV[count]];
          Pos next = actual + direc_D[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                  Q.push(make_pair(next, direc_D[count]));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            
            //Hacemos reshuffle del vector random
            randomV = random_permutation(8);
            
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Casilla neutra encontrada
            if (cell(P).id == -1 and cell(P).type != Outside and not Ocupat[P.i][P.j]) {
                return dirini;
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 8; ++count) {
                    Pos next = P + direc_D[randomV[count]];
                    if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
        
        //WTF?!?!?!?
        return None;
    }
    
    //BFS para ir hacia cuevas enemigas, con diagonales
    Dir bfs_conquer_enemigo(Pos actual, VVB Ocupat) {

        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        
        //Vector random para más eficiencia en el bfs
        randomV = random_permutation(8);
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales sin diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] and [no hay nadie] and [no visitado] and [no ocupado]
        for (int count = 0; count < 8; ++count) {
          dirini = direc_D[randomV[count]];
          Pos next = actual + direc_D[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                  Q.push(make_pair(next, direc_D[count]));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            
            //Hacemos reshuffle del vector random
            randomV = random_permutation(8);
            
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Casilla enemiga encontrada
            if (cell(P).owner != -1 and cell(P).owner != me() and cell(P).type != Outside and not Ocupat[P.i][P.j]) {
                return dirini;
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 8; ++count) {
                    Pos next = P + direc_D[randomV[count]];
                    if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
        
        
        //No hay casillas enemigas, ve a por tesoros
        return None;
    }
    
    //BFS para pegarse, con diagonales
    Dir bfs_enemigo(Pos actual, VVB Ocupat) {
        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales sin diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] and [no visitado] and [no ocupado]
        for (int count = 0; count < 8; ++count) {
          dirini = direc_D[count];
          Pos next = actual + direc_D[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                  Q.push(make_pair(next, direc_D[count]));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Enemigo encontrado
            if (cell(P).id != -1){
                if (unit(cell(P).id).player != me()) {
                    return dirini;
                }
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 8; ++count) {
                    Pos next = P + direc_D[count];
                    if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
        
        //No se puede llegar a ningún enemigo
        return None;
    }
    
    //BFS para huir de enemigos, sin diagonales
    Dir bfs_huir(Pos actual, VVB Ocupat) {
        
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el command
        
        //Direcciones iniciales sin diagonales
        //Condiciones: [pos_ok] or [es cueva] or [es outside] and [no hay nadie] and [no visitado] and [no ocupado]
        for (int count = 0; count < 4; ++count) {
          dirini = direc[count];
          Pos next = actual + direc[count];
          if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and cell(next).id == -1 and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                  Q.push(make_pair(next, direc[count]));
          }
        }
        
        //Ve iterando
        while (not Q.empty()) {
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Enemigo encontrado
            if (cell(P).id != -1){
                if (unit(cell(P).id).player != me()) {
                    P = actual + opposite(dirini);
                    if (pos_ok(P) and (cell(P).type != Rock and cell(P).type != Abyss and cell(P).type != Granite)) return opposite(dirini);
                    else return None;
                }
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 4; ++count) {
                    Pos next = P + direc[count];
                    if (pos_ok(next) and ((cell(next).type == Cave or cell(next).type == Outside) and cell(next).id == -1 and (not Visitado[next.i][next.j]) and (not Ocupat[next.i][next.j]))) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
        
        //Acepta tu destino, no puedes escapar
        return None;
    }
    
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      
      //Matriz de sitios ocupados por unidades en ese momento
      VVB Ocupat = VVB (rows(),VB(cols(), false));
      
      //Vectores de mis cosas
      vector<int> negros = dwarves(me());
      vector<int> magos = wizards(me());
      
      int tamNegros = negros.size();
      int tamMagos = magos.size();
      
    
    //LOS NEGROS    ---     Trabajan como los de la vida real
    for (int i = 0; i < tamNegros; ++i) {
        int dniN = negros[i];  //DNI del negro que trabajará ahora
        Unit negro = unit(dniN);
        
        //Matriz de visitado para los dfs (reset)
        visitado = VVB(rows(),VB(cols(), false));
        
        //Prioridad: TODOS: Pegarse si tienen un mago o son atacados > ir a por tesoros si están cerca > conquer random
        
        if (mago_cerca(negro.pos, 2) or enemigo_cerca_D(negro.pos, 1)) {
            Dir palla = bfs_enemigo(negro.pos, Ocupat);
            command(dniN, palla);
            Ocupat[(negro.pos + palla).i][(negro.pos + palla).j] = true;
        }
        
        else if (tesoro_cerca_D(negro.pos, 25, visitado)) {
            Dir palla = bfs_tesoro(negro.pos, Ocupat);
            command(dniN, palla);
            Ocupat[(negro.pos + palla).i][(negro.pos + palla).j] = true;
        }
        
        else {
            decision = random(0, 1);
            
            if (decision) {
                Dir palla = bfs_conquer_enemigo(negro.pos, Ocupat);
                command(dniN, palla);
                Ocupat[(negro.pos + palla).i][(negro.pos + palla).j] = true;                
            }
            
            else {
                Dir palla = bfs_conquer_neutral(negro.pos, Ocupat);
                command(dniN, palla);
                Ocupat[(negro.pos + palla).i][(negro.pos + palla).j] = true;  
            }
        }
        
        
    }

    //LOS MAGOS     ---     No hacen mucho y no son muy listos
    for (int i = 0; i < tamMagos; ++i) {
        int dniM = magos[i];    //DNI del mago que hará cosas ahora
        Unit mago = unit(dniM);
        
        //Si le atacan, huir
        if (enemigo_cerca_D(mago.pos, 1)) {
            //Correr
            Dir palla = bfs_huir(mago.pos, Ocupat);
            command(dniM, palla);
            Ocupat[(mago.pos + palla).i][(mago.pos + palla).j] = true;
        }
        
        else {
            //Ir hacia dwarves aliados
            Dir palla = bfs_dwarf(mago.pos, Ocupat);
            command(dniM, palla);
            Ocupat[(mago.pos + palla).i][(mago.pos + palla).j] = true;
        }
    }
    
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
