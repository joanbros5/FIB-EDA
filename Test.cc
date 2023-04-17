#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

//Ordre customizado de la priority queue
class meu_ordre {
public:
    
    //Reotrna true si p1 > p2 i False en cas contrari
    bool operator()(const pair<int,int>& p1,
                    const pair<int,int>& p2)
    {
          return p1.first + p1.second > p2.first + p2.second;            
    }
    
};

//MAIN
int main() {
    cout << "-----Priority queues-----" << endl;
    //Priority queues
    priority_queue<pair<int,int>, vector<pair<int, int>>, meu_ordre> Q;
    Q.push({2,4});
    Q.push({1,7});
    Q.push({3,2});
    Q.push({8,3});
    
    while (not Q.empty()) {
        pair<int,int> x = Q.top();
        Q.pop();
        cout << x.first << " " << x.second << endl;
    }
    
    cout << "-----Sets-----" << endl;
    //Sets
    set<int> S;
    S.insert(2);
    S.insert(-6);
    S.insert(17);
    S.insert(7);
    auto p = S.insert(9);
    auto q = S.insert(9);
    
    cout << p.second << " " << q.second << endl;
    
    for (int x : S) cout << x << endl;
    
    //Primer element
    auto it = S.begin();
    cout << *it << endl;
    
    //Ultim element
    it = S.end();
    --it;
    cout << *it << endl;
    
    
    cout << "-----Cosas de vectores-----" << endl;
    //Cosas de vectores
    vector<int> v = {1,3,5,2,7,4};
    for (auto& x : v) cout << x << endl;
    
    
    cout << "-----Maps-----" << endl;
    //Maps
    map<string,int> M;
    M.insert({"Joan",5});
    M.insert({"Leo",7});
    M.insert({"Pau",8});
    M.insert({"Marta",1});
    
    cout << "Size: " << M.size() << endl;
    
    for (auto& p : M) {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
    
    //Marta té un punt més
    cout << "Marta té un punt més" << endl;
    
    ++M["Marta"];
    
    for (auto& p : M) {
        cout << p.first << " " << p.second << endl;
    }
    
    //Marta s'ha desmatriculat
    cout << endl;
    cout << "Marta s'ha desmatriculat" << endl;
    
    M.erase("Marta");
    
    for (auto& p : M) {
        cout << p.first << " " << p.second << endl;
    }
}
