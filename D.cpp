#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 1005

struct help{
  vector <int> path;
  map <vector <int>, bool> used;
  int len;
  help(){}
  help(vector <int> a){
    path = a;
    len = sz(a);
  }
};

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

bool check(vector <int> &a, vector <int> &b){
  if(sz(b) > sz(a)){
    return false;
  }
  int j, i;
  for(i = 0, j = 0; i < sz(a) and j < sz(b); i++){
    if(a[i] == b[j]){
      j++;
    }
  }
  return (j == sz(b));
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
  vector <help> queries;
  while(q--){
    int u, v;
    cin >> u >> v;
    queries.push_back(help(lca(u, v)));
  }
  for(int i = 0; i < sz(queries); i++){
    for(int j = 0; j < sz(queries); j++){
      if(i == j){
        continue;
      }
      if(queries[i].used.count(queries[j].path) == 0){
        if(check(queries[i].path, queries[j].path)){
          queries[i].used[queries[j].path];
          queries[i].len -= (sz(queries[j].path)-1);
        }
      }
    }
  }
  int tot = 0;
  for(auto i : queries){
    tot += i.len;
  }
  cout << tot << "\n";
  return 0;
}
