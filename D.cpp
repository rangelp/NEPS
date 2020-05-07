#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 100005

vector <int> g[maxn];
int parent[maxn], lvl[maxn];

vector <int> lca(int u, int v){
  vector <int> Pu = {u}, Pv = {v};
  while(lvl[u] != lvl[v]){
    if(lvl[u] > lvl[v]){
      u = parent[u];
      Pu.push_back(u);
    }
    else{
      v = parent[v];
      Pv.push_back(v);
    }
  }
  while(u != v){
    u = parent[u];
    Pu.push_back(u);
    v = parent[v];
    Pv.push_back(v);
  }
  for(int i = sz(Pv)-2; i >= 0; i--){
    Pu.push_back(Pv[i]);
  }
  return Pu;
}

void dfs(int u, int p, int h){
  parent[u] = p;
  lvl[u] = h;
  for(auto v : g[u]){
    if(v != p){
      dfs(v, u, h+1);
    }
  }
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  for(int i = 0; i < n-1; i++){
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 1, 1);
  int q;
  cin >> q;
  vector <vector <int>> queries;
  while(q--){
    int u, v;
    cin >> u >> v;
    queries.push_back(lca(u, v));
  }
  
  return 0;
}
