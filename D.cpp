#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(args...){string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args);}
#define endl "\n"

void err(istream_iterator<string> it){}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args){
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 1005

vector <int> g[maxn];
int parent[maxn], lvl[maxn];

vector <int> lca(int u, int v){
  vector <int> Pu = {u}, Pv = {v};
  while(lvl[u] != lvl[v]){
    if(lvl[u] > lvl[v]){
      u = parent[u];
      Pu.emplace_back(u);
    }
    else{
      v = parent[v];
      Pv.emplace_back(v);
    }
  }
  while(u != v){
    u = parent[u];
    Pu.emplace_back(u);
    v = parent[v];
    Pv.emplace_back(v);
  }
  for(int i = sz(Pv)-2; i >= 0; i--){
    Pu.emplace_back(Pv[i]);
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

int inside(vector <int> &a, vector <int> &b){
  for(int i = 0; i < sz(a)-sz(b)+1; i++){
    int j = 0;
    for(j = 0; j < sz(b); j++){
      if(a[i+j] != b[j]){
        break;
      }
    }
    if(j == sz(b)){
      return i;
    }
  }
  return -1;
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  for(int i = 0; i < n-1; i++){
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  dfs(1, 1, 1);
  int q;
  cin >> q;
  vector <int> queries[q];
  for(int i = 0; i < q; i++){
    int u, v;
    cin >> u >> v;
    queries[i] = (lca(u, v));
  }
  vector <tuple <int, int, int>> in[q];
  for(int i = 0; i < q; i++){
    for(int j = 0; j < q; j++){
      if(i == j){
        continue;
      }
      int pos = inside(queries[i], queries[j]);
      if(pos != -1){
        in[i].emplace_back(make_tuple(j+1, pos, pos+sz(queries[j])-1));
      }
    }
  }
  for(int i = 0; i < q; i++){
    sort(in[i].begin(), in[i].end(), [](tuple <int, int, int> &a, tuple <int, int, int> &b){
      int ai, aj, ak, bi, bj, bk;
      tie(ai, aj, ak) = a;
      tie(bi, bj, bk) = b;
      if(aj == bj){
        return ak <= bk;
      }
      return aj <= bj;
    });
  }
  int ans = 0;
  for(int i = 0; i < q; i++){
    ans += sz(queries[i]);
    int N = sz(in[i]);
    int dp[N+1] = {0};
    for(int _i = N-1; _i >= 0; _i--){
      int l, r;
      tie(ignore, l, r) = in[i][_i];
      int rg = r-l;
      dp[_i] = max(dp[_i+1], rg);
      for(int _j = _i+1; _j < N; _j++){
        if(get <1> (in[i][_j]) > get <2> (in[i][_i])){
          dp[_i] = max(dp[_i], rg+dp[_j]);
        }
      }
    }
    ans -= dp[0];
  }
  cout << ans << endl;
  return 0;
}
