#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

struct user{
  string name;
  int xp, lvl;
  user(){}
  user(string s){
    name = s;
    xp = 25;
    lvl = 1;
  }
  void add(){
    xp += 25;
    if(xp%100 == 0){
      lvl++;
    }
  }
};

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  map <string, int> users;
  vector <user> robot;
  vector <int> lastmsg;
  int cnt = 0;
  for(int i = 0; i < n; i++){
    string s;
    int w;
    cin >> s >> w;
    if(users.count(s) == 0){
      users[s] = cnt;
      robot.push_back(user(s));
      lastmsg.push_back(w);
      cnt++;
    }
    if(lastmsg[users[s]]+k <= w){
      lastmsg[users[s]] = w;
      robot[users[s]].add();
    }
  }
  sort(robot.begin(), robot.end(), [](user a, user b){
    if(a.xp == b.xp){
      return a.name < b.name;
    }
    return a.xp > b.xp;
  });
  while(sz(robot) < 3){
    robot.push_back(user(""));
  }
  cout << "--Rank do Nepscord--\n";
  for(int i = 0; i < 3; i++){
    cout << "#" << i+1 << ".";
    if(robot[i].name == ""){
      cout << "\n";
    }
    else{
      cout << " " << robot[i].name << " - Nivel " << robot[i].lvl << "\n";
    }
  }
  return 0;
}
