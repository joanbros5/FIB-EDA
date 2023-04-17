#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0} };

bool bon_vei (const vector<vector<char>>& M, int i, int j) {
  return i >= 0 and j >= 0 and i < M.size() and j < M[0].size() and M[i][j] != 'X';
}

int dfs_tresor (vector<vector<char>>& M, int orig_i, int orig_j, int res) {
  // Pre: M[orig_i][orig_j] != 'X'
  
  if (M[orig_i][orig_j] == 't') return 1;
  if (M[orig_i][orig_j] == 'X') return 0;

  M[orig_i][orig_j] = 'X';
  
  for (auto& d : dirs) {
    int v_i = orig_i + d.first;
    int v_j = orig_j + d.second;
    // (v_i,v_j) es un possible vei de (orig_i,orig_j)
    if (bon_vei(M,v_i,v_j))
      res += dfs_tresor(M,v_i,v_j,res);
  }

  return res;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<char>> M(n,vector<char>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> M[i][j];
  int orig_i, orig_j;
  cin >> orig_i >> orig_j;
    
  int res = 0;
  cout << dfs_tresor(M, orig_i, orig_j, res) << endl;
}
