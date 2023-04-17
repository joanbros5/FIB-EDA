#include <iostream>
#include <map>
using namespace std;


int main() {
    string operacio;
    int x;
    double avg;
    map<int,int> lista;
    
    while (cin >> operacio) {
        if (operacio == "number") {
            cin >> x;
        }
        
        else if (operacio == "delete") {
            
        }
        
        if (not lista.empty()) {
            cout << "minimun: " << min << ", maximum: " << max << ", average: " << avg << endl;
        }
        else cout << "no elements" << endl;
    }
}
