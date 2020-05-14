#include <bits/stdc++.h>

using namespace std;

#define aint(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long int ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 100040

struct node{
  ll xor_seq, or_seq, and_seq;
  int mn, mx;
  node(){}
  node(ll xor_seq, ll or_seq, ll and_seq, int mn, int mx){
    this->xor_seq = xor_seq;
    this->or_seq = or_seq;
    this->and_seq = and_seq;
    this->mn = mn;
    this->mx = mx;
  }
};

node segtree[4*maxn];
ll arr[maxn];

int _min(int a, int b){
  return arr[a] < arr[b] ? a : b;
}

int _max(int a, int b){
  return arr[a] > arr[b] ? a : b;
}

node combine(node a, node b){
  return node(a.xor_seq^b.xor_seq, a.or_seq|b.or_seq, a.and_seq&b.and_seq, _min(a.mn, b.mn), _max(a.mx, b.mx));
}

void build(int i, int l, int r){
  if(l == r){
    segtree[i] = node(arr[l], arr[l], arr[l], l, l);
    return;
  }
  int md = (l+r)/2, nxt = 2*i;
  build(nxt, l, md);
  build(nxt+1, md+1, r);
  segtree[i] = combine(segtree[nxt], segtree[nxt+1]);
}

void update(int i, int l, int r, int p, int var){
  if(l > p or r < p){
    return;
  }
  if(l == p and r == p){
    arr[l] = var;
    segtree[i] = node(arr[l], arr[l], arr[l], l, l);
    return;
  }
  int md = (l+r)/2, nxt = 2*i;
  update(nxt, l, md, p, var);
  update(nxt+1, md+1, r, p, var);
  segtree[i] = combine(segtree[nxt], segtree[nxt+1]);
}

node query(int i, int l, int r, int x, int y){
  if(l > y or r < x){
    return node(0, 0, -1, maxn-1, maxn-2);
  }
  if(l >= x and r <= y){
    return segtree[i];
  }
  int md = (l+r)/2, nxt = 2*i;
  return combine(query(nxt, l, md, x, y), query(nxt+1, md+1, r, x, y));
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
  }
  arr[maxn-1] = (1LL<<56);
  arr[maxn-2] = -(1LL<<56);
  build(1, 0, n-1);
  while(q--){
    char op;
    int x, y;
    cin >> op >> x >> y;
    x--, y--;
    if(op == 'x'){
      node a = query(1, 0, n-1, x, y);
      cout << (a.xor_seq == 0 ? arr[a.mx] : -1) << "\n";
    }
    else if(op == 'o'){
      int id = query(1, 0, n-1, x, y).mx;
      ll L = 0, R = 0;
      if(id != x){
        L = query(1, 0, n-1, x, id-1).or_seq;
      }
      if(id != y){
        R = query(1, 0, n-1, id+1, y).or_seq;
      }
      //L = query(1, 0, n-1, x, id-1).or_seq, R = query(1, 0, n-1, id+1, y).or_seq;
      ll OR = L|R;
      cout << (OR == arr[id] ? arr[id] : -1) << "\n";
    }
    else if(op == 'a'){
      int id = query(1, 0, n-1, x, y).mn;
      ll L = -1, R = -1;
      if(id != x){
        L = query(1, 0, n-1, x, id-1).and_seq;
      }
      if(id != y){
        R = query(1, 0, n-1, id+1, y).and_seq;
      }
      //L = query(1, 0, n-1, x, id-1).and_seq, R = query(1, 0, n-1, id+1, y).and_seq;
      ll AND = L&R;
      cout << (AND == arr[id] ? arr[id] : -1) << "\n";
    }
    else{
      update(1, 0, n-1, x, y+1);
    }
  }
  return 0;
}
