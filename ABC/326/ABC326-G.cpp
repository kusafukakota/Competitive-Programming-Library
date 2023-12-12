#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<ll> c(n), a(m);
  vector<vector<ll>> v(m, vector<ll>(n));
  for(auto &i : c) { cin >> i; }
  for(auto &i : a) { cin >> i; }
  for(auto &i : v) {
    for(auto &j : i) { cin >> j; }
  }
  mf_graph<ll> g(n * 5 + m + 2);
  ll S = n * 5 + m, T = n * 5 + m + 1;
  for(ll i = 0; i < n; i++) {
    for(ll j = 1; j < 5; j++) {
      g.add_edge(S, i * 5 + j, c[i]);
    }
    for(ll j = 0; j < 5; j++) {
      for(ll k = j + 1; k < 5; k++) {
        g.add_edge(i * 5 + j, i * 5 + k, 1e18);
      }
    }
  }
  ll r = accumulate(a.begin(), a.end(), ll(0));
  for(ll i = 0; i < m; i++) {
    g.add_edge(S, n * 5 + i, 0);
    g.add_edge(n * 5 + i, T, a[i]);
    for(ll j = 0; j < n; j++) {
      g.add_edge(j * 5 + v[i][j] - 1, n * 5 + i, 1e18);
    }
  }
  cout << r - g.flow(S, T) << "\n";
}

// 燃やす埋める
