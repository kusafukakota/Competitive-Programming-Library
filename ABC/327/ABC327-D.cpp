#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> bipartite(vector<vector<ll>> &g) {
  ll n = g.size();
  vector<ll> color(n, -1);
  function<bool(ll, ll)> DFS = [&](ll v, ll c) {
    color[v] = c;
    for(auto &nv : g[v]) {
      if(color[nv] != -1) {
        if(color[nv] == c) { return false; }
        continue;
      }
      if(!DFS(nv, 1 - c)) { return false; }
    }
    return true;
  };
  for(ll i = 0; i < n; i++) {
    if(color[i] == -1) {
      if(!DFS(i, 0)) { return {}; }
    }
  }
  return color;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<ll> a(m), b(m);
  for(auto &i : a) {
    cin >> i;
    i--;
  }
  for(auto &i : b) {
    cin >> i;
    i--;
  }
  vector<vector<ll>> g(n);
  for(ll i = 0; i < m; i++) {
    g[a[i]].emplace_back(b[i]);
    g[b[i]].emplace_back(a[i]);
  }
  auto r = bipartite(g);
  cout << (ssize(r) ? "Yes" : "No") << "\n";
}
