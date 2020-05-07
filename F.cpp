#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 100005
#define LOG 20

vector <int> g[maxn];
int dp[maxn][LOG], arr[maxn], lvl[maxn], subtree[maxn];
int head[maxn], chain[maxn], posarr[maxn], inhld[maxn];
long long int segtree[4*maxn], lazy[4*maxn];
int cnt, pos;

long long int combine(long long int a, long long int b){
  return a|b;
}

void build(int i, int l, int r){
  if(l == r){
    segtree[i] |= (1LL<<inhld[posarr[l]]);
    return;
  }
  int md = (l+r)/2, nxt = 2*i;
  build(nxt, l, md);
  build(nxt+1, md+1, r);
  segtree[i] = combine(segtree[nxt], segtree[nxt+1]);
}

void push(int i, int l, int r){
  if(lazy[i]){
    segtree[i] = lazy[i];
    if(l != r){
      int nxt = 2*i;
      lazy[nxt] = lazy[i];
      lazy[nxt+1] = lazy[i];
    }
    lazy[i] = 0;
  }
}

void update(int i, int l, int r, int x, int y, int var){
  push(i, l, r);
  if(l > y or r < x){
    return;
  }
  if(l >= x and r <= y){
    lazy[i] = 1LL<<var;
    push(i, l, r);
    return;
  }
  int md = (l+r)/2, nxt = 2*i;
  update(nxt, l, md, x, y, var);
  update(nxt+1, md+1, r, x, y, var);
  segtree[i] = combine(segtree[nxt], segtree[nxt+1]);
}

long long int query(int i, int l, int r, int x, int y){
  push(i, l, r);
  if(l > y or r < x){
    return 0;
  }
  if(l >= x and r <= y){
    return segtree[i];
  }
  int md = (l+r)/2, nxt = 2*i;
  return combine(query(nxt, l, md, x, y), query(nxt+1, md+1, r, x, y));
}

void hld(int u, int p, int var){
  if(head[cnt] == -1){
    head[cnt] = u;
  }
  chain[u] = cnt;
  posarr[u] = pos;
  inhld[pos++] = var;
  int id = -1, sz = -1;
  for(auto v : g[u]){
    if(v != p and subtree[v] > sz){
      sz = subtree[v];
      id = v;
    }
  }
  if(id != -1){
    hld(id, u, arr[id]);
  }
  for(auto v : g[u]){
    if(v != p and v != id){
      cnt++;
      hld(v, u, arr[v]);
    }
  }
}

void dfs(int u, int p, int h){
  dp[u][0] = p;
  lvl[u] = h;
  subtree[u] = 1;
  for(int i = 1; i < LOG; i++){
    if(dp[u][i-1] != -1){
      dp[u][i] = dp[dp[u][i-1]][i-1];
    }
  }
  for(auto v : g[u]){
    if(v != p){
      dfs(v, u, h+1);
      subtree[u] += subtree[v];
    }
  }
}

int lca(int u, int v){
  if(lvl[u] > lvl[v]){
    swap(u, v);
  }
  for(int i = LOG-1; i >= 0; i--){
    if(dp[v][i] != -1 and lvl[dp[v][i]] >= lvl[u]){
      v = dp[v][i];
    }
  }
  if(u == v){
    return v;
  }
  for(int i = LOG-1; i >= 0; i--){
    if(dp[v][i] != dp[u][i]){
      u = dp[u][i];
      v = dp[v][i];
    }
  }
  return dp[v][0];
}

long long int solveQuery(int u, int v){
  int chainU = chain[u], chainV = chain[v];
  long long int ans = 0;
  while(true){
    chainU = chain[u];
    if(chainU == chainV){
      ans = combine(ans, query(1, 0, pos-1, posarr[v], posarr[u]));
      break;
    }
    ans = combine(ans, query(1, 0, pos-1, posarr[head[chainU]], posarr[u]));
    u = head[chainU];
    u = dp[u][0];
  }
  return ans;
}

void solveUpdate(int u, int v, int var){
  int chainU = chain[u], chainV = chain[v];
  while(true){
    chainU = chain[u];
    if(chainU == chainV){
      update(1, 0, pos-1, posarr[v], posarr[u], var);
      break;
    }
    update(1, 0, pos-1, posarr[head[chainU]], posarr[u]+1, var);
    u = head[chainU];
    u = dp[u][0];
  }
}

long long int solveQuery(int u, int v, int _lca){
  if(u != _lca and v != _lca){
    return combine(solveQuery(u, _lca), solveQuery(v, _lca));
  }
  if(u == _lca){
    return solveQuery(v, u);
  }
  return solveQuery(u, v);
}

void solveUpdate(int u, int v, int _lca, int var){
  if(u != _lca and v != _lca){
    solveUpdate(u, _lca, var);
    solveUpdate(v, _lca, var);
  }
  else if(u == _lca){
    solveUpdate(v, u, var);
  }
  else{
    solveUpdate(u, v, var);
  }
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
  }
  for(int i = 0; i < n-1; i++){
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  memset(dp, -1, sizeof dp);
  memset(head, -1, sizeof  head);
  cnt = pos = 0;
  dfs(0, 0, 0);
  hld(0, 0, arr[0]);
  build(1, 0, pos-1);
  int q;
  cin >> q;
  while(q--){
    int op;
    cin >> op;
    if(op&1){
      int u, w;
      cin >> u >> w;
      u--;
      solveUpdate(u, u, u, w);
    }
    else{
      int u, v;
      cin >> u >> v;
      u--, v--;
      cout <<  __builtin_popcountll(solveQuery(u, v, lca(u, v))) << "\n";
    }
  }
  return 0;
}
