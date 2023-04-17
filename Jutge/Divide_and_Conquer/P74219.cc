#include <iostream>
using namespace std;

int Fibonacci(int& n) {
    if (n <= 2) return 1;
    int numant = 0, num = 0, postnum;
    for (int i = 0; i < n; ++i) {
        if (num == 0) num++;
        else {
            postnum = num+numant;
            numant = num;
            num = postnum;
        }
    }
    cout << "El numero que me ha salido es " << num << endl;
    return num;
}

int main() {
    int n,m;
    while (cin >> n >> m) {
        cout << Fibonacci(n) % m << endl;
    }
}
