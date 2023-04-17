#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Joantibiotic


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  
    using VB = vector<bool>;
    using VVB = vector<VB>;
    using VE = vector<int>;
    using VVE = vector<VE>;
    
    bool kamikaze;
    const vector<Dir> direc = {TOP, RIGHT, BOTTOM, LEFT};   //Direcciones por defecto
    VVE ciudades = VVE(rows(), VE(cols(), -1));             //Matriz de ciudades sin reclamar por mí (Funciona con DNIs)
    
    //DFS para saber si hay un enemigo en un radio x
    bool enemigo_cerca(Pos actual, int x) {
        if (not pos_ok(actual)) return false;
        if (x < 0) return false;
        else {
          Cell cuadrado = cell(actual);
          Unit alguien = unit(cuadrado.unit_id);
          if (alguien.player != me()) return true;
          return enemigo_cerca(actual + TOP, x-1) or enemigo_cerca(actual + RIGHT, x-1) or
          enemigo_cerca(actual + BOTTOM, x-1) or enemigo_cerca(actual + LEFT, x-1);
      }
    }
    
    /*  DFS para saber cuántos enemigos hay en una ciudad         PENDIENTE!!!!!!!!!!!
    int enemigos_ciudad(Pos actual) {
        if (not pos_ok(actual)) return 0;
    }
    */
    
    //BFS para los kamikazes, hacia enemigos                   
    Dir bfs_kamikaze(Pos actual, VVB Ocupat) {
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        Q.push(make_pair(actual, direc[0]));
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el move
        for (int count = 0; count < 4; ++count) {
          dirini = direc[count];
          Pos next = actual + direc[count];
          if (pos_ok(next) and (cell(next).type == GRASS or cell(next).type == CITY or cell(next).type == PATH or cell(next).type != WALL) and not Visitado[next.i][next.j] and not Ocupat[next.i][next.j]) {
                  Q.push(make_pair(next, direc[count]));
          }
        }
        
        while (not Q.empty()) {
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Enemigo encontrado
            if (unit(cell(P).unit_id).player != me() and unit(cell(P).unit_id).player != -1 and not Ocupat[P.i][P.j]) {
                return dirini;
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 4; ++count) {
                    Pos next = P + direc[count];
                    if (pos_ok(next) and (cell(next).type == GRASS or cell(next).type == CITY or cell(next).type == PATH or cell(next).type != WALL) and not Visitado[next.i][next.j] and not Ocupat[next.i][next.j]) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
          
        return NONE; //No se ha podido llegar a ningún enemigo
    }
    
    //BFS para ir hacia ciudades o paths                        
    Dir bfs_ciudad(Pos actual, VVB Ocupat) {
        VVB Visitado = VVB (rows(),VB(cols(), false));
        queue<pair<Pos, Dir>> Q;
        Visitado[actual.i][actual.j] = true;
        Q.push(make_pair(actual, direc[0]));
        
        Dir dirini; //Dirección que se toma inicialmente, para devolver en el move
        for (int count = 0; count < 4; ++count) {
          dirini = direc[count];
          Pos next = actual + direc[count];
          if (pos_ok(next) and (cell(next).type == GRASS or cell(next).type == CITY or cell(next).type == PATH or cell(next).type != WALL) and not Visitado[next.i][next.j] and not Ocupat[next.i][next.j]) {
                  Q.push(make_pair(next, direc[count]));
          }
        }
        
        while (not Q.empty()) {
            Pos P = Q.front().first;
            dirini = Q.front().second;
            Q.pop();
            
            //Ciudad o Path encontrado
            if ((cell(P).type == PATH or cell(P).type == CITY) and not Ocupat[P.i][P.j]) {
                if (cell(P).type == CITY) {
                    if (city_owner(cell(P).city_id) != me())
                        return dirini;
                }
                else if (cell(P).type == PATH) {
                    if (path_owner(cell(P).path_id) != me())
                        return dirini;
                }
            }
            
            else if (not Visitado[P.i][P.j]) {
                Visitado[P.i][P.j] = true;
                for (int count = 0; count < 4; ++count) {
                    Pos next = P + direc[count];
                    if (pos_ok(next) and (cell(next).type == GRASS or cell(next).type == CITY or cell(next).type == PATH or cell(next).type != WALL) and not Visitado[next.i][next.j] and not Ocupat[next.i][next.j]) {
                        Q.push(make_pair(next, dirini));
                    }
                }
            }
        }
          
        return NONE; //No se ha podido llegar a ningún enemigo
    }
    
    
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      
      VVB Ocupado = VVB (rows(),VB(cols(), false));
      VE ejercito = my_units(me());
      int tamEjercito = ejercito.size();
      
      //Cada unidad mía hace:
      for (int i = 0; i < tamEjercito; ++i) {
          
          int dni = ejercito[i];        //DNI del soldado i
          Unit soldado = unit(dni);     //Unidad que se trata en ese momento
          Cell casilla = cell(soldado.pos);
          
          //Si la unidad está infectada, es un kamikaze
          kamikaze = soldado.damage > 0;
          
          
          //Las cuatro casillas adyacentes
        for (int count = 0; count < 4; ++count) {
                    Pos next = soldado.pos + direc[count];
                    //Hay una mascarilla
                    if (pos_ok(next) and (cell(next).mask) and not Ocupado[next.i][next.j]) {
                        move(dni, direc[count]);
                        Ocupado[next.i][next.j] = true;
                    }
                    
                    //Hay un enemigo
                    else if (pos_ok(next) and unit(cell(next).unit_id).player != me() and unit(cell(next).unit_id).player != -1 and not Ocupado[next.i][next.j]) {
                        move(dni, direc[count]);
                        Ocupado[next.i][next.j] = true;
                    }
        }
          
          
        //No hay una mascarilla adyacente
        if (true) {
            //Soldado está en GRASS
            if (casilla.type == GRASS) {
                //Está infectado y hay un enemigo cerca
                
                if (kamikaze and enemigo_cerca(soldado.pos, soldado.damage)) {
                    Dir palla = bfs_ciudad(soldado.pos, Ocupado);
                    move(dni,palla);
                    Ocupado[(soldado.pos + palla).i][(soldado.pos + palla).j] = true;
                }
                //No está infectado o sí lo está pero no hay enemigos
                else {
                    
                    Dir palla = bfs_ciudad(soldado.pos, Ocupado);
                    move(dni, palla);
                    Ocupado[(soldado.pos + palla).i][(soldado.pos + palla).j] = true;
                }
            }
            //Soldado está en city o path
            else {
                //Si hay un enemigo a rango 3 ir a por él
                
                if (enemigo_cerca(soldado.pos, 2)) {
                    Dir palla = bfs_ciudad(soldado.pos, Ocupado);
                    move(dni, palla);
                    Ocupado[(soldado.pos + palla).i][(soldado.pos + palla).j] = true;
                }
                
                
                //Por defecto, si todo está OK, seguir buscando ciudades o paths
                Dir palla = bfs_ciudad(soldado.pos, Ocupado);
                move(dni, palla);
                Ocupado[(soldado.pos + palla).i][(soldado.pos + palla).j] = true;
            }
          
          }
        }
    }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
