#include <iostream>
#include <set>
#include <string>
#include <stdlib.h> 
using namespace std;


struct strsize {
	bool operator() (const string& a, const string& b) const {
		if (a.size() < b.size()) return true;
		else if (a.size() > b.size()) return false;
		else return a < b;
	}
};


int game = 1;
set<string> estan;
set<string, strsize> hanestado;

void esborra_sets() {
    estan.clear();
    hanestado.clear();
}

//Escribir en formato de salida
void escriu_game() {
    cout << "GAME #" << game << endl;
    cout << "HAS:" << endl << endl;
    
    auto it = estan.begin();
    while (it != estan.end()) {
        cout << *it << endl;
        ++it;
    }
    
    cout << endl;
    
    cout << "HAD:" << endl;
    
    it = hanestado.begin();
    while (it != hanestado.end()) {
        cout << *it << endl;
        ++it;
    }
    
    cout << endl;
}

//MAIN
int main() {
    string word;
    bool end = false;
    
    while (cin >> word and not end) {
        
        //DEBUG
        //cout << "He leido la palabra " << word << endl;
        
        if (word == "END") {
            escriu_game();
            esborra_sets();
            ++game;
        }
        
        else if (word == "QUIT") {
            escriu_game();
            end = true;
        }
        
        else {
            
            auto it = estan.find(word);
            
            if (it == estan.end()) {
                estan.insert(word);
                hanestado.erase(word);
            }
            else {
                estan.erase(word);
                hanestado.insert(word);
            }
        }
        
    }
}
