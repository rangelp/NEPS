#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 351
#define oo -100000000

int n, m, p, dx[] = {1, 0, 0}, dy[] = {0, -1, 1};
string g[maxn][maxn];
int dp[maxn][maxn][1<<4][6][3];
short int see[maxn][maxn][1<<4][6][3];

bool in(int x, int y){
  if(x < 0 or x >= n or y < 0 or y >= m){
    return false;
  }
  return true;
}

int get(string s){
  if(s == "N"){
    return 0;
  }
  if(s == "O"){
    return 1;
  }
  if(s == "K"){
    return 2;
  }
  return 3;
}

bool isalpha(string s){
  return (s.find("N") != string::npos or s.find("O") != string::npos
          or s.find("K") != string::npos or s.find("A") != string::npos); 
}

int solve(int x, int y, int bt, int k, int dir){
  if(x == n-1 and y == m-1){
    if(k){
      return 0;     
    }
    return stoi(g[x][y]);
  }
  int &ans = dp[x][y][bt][k][dir];
  if(see[x][y][bt][k][dir] != 0){
    return ans;
  }
  see[x][y][bt][k][dir] = 1;
  for(int i = 0; i < 3; i++){
    if((dir == 1 and i == 2) or (dir == 2 and i == 1)){
      continue;
    }
    int _x = x+dx[i], _y = y+dy[i];
    if(in(_x, _y)){
      if(k){
        ans = max(ans, solve(_x, _y, bt, max(k-1, 0), i));
      }
      else if(isalpha(g[x][y])){
        if(__builtin_popcount(bt) == 4){
          ans = max(ans, solve(_x, _y, 0, p-1, i));
        }
        int _bt = bt|(1<<get(g[x][y]));
        ans = max(ans, solve(_x, _y, _bt, k, i));
      }
      else{
        if(__builtin_popcount(bt) == 4){
          ans = max(ans, solve(_x, _y, 0, p-1, i));
        }
        ans = max(ans, stoi(g[x][y])+solve(_x, _y, bt, k, i));
      }
    }
  }
  return ans;
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  cin >> n >> m >> p;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> g[i][j];
    }
  }
  for(int i = 0; i < maxn; i++){
    for(int j = 0; j < maxn; j++){
      for(int k = 0; k < 1<<4; k++){
        for(int l = 0; l < 6; l++){
          for(int _m = 0; _m < 3; _m++){
            dp[i][j][k][l][_m] = -0x3f3f3f3f;
            see[i][j][k][l][_m] = 0;
          }
        }
      }
    }
  }
  cout << solve(0, 0, 0, 0, 0) << "\n";
  return 0;
}
