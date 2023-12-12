#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, a, b, c;
  cin >> n >> a >> b >> c;
  vector<vector<pair<ll, ll>>> g(n);
  vector<vector<ll>> v(n, vector<ll>(n));
  for(auto &i : v) {
    for(auto &j : i) { cin >> j; }
  }
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < n; j++) {
      // if(i == j) { continue; }
      g[i].emplace_back(j, v[i][j]);
    }
  }
  vector<ll> d(n, 1e18);
  d[0] = 0;
  auto chmin = [&](auto &a, const auto &b) { return a > b ? (a = b, true) : false; };
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
  q.emplace(0, 0);
  while(!q.empty()) {
    auto [tmp, v] = q.top();
    q.pop();
    if(tmp > d[v]) { continue; }
    for(auto &[nv, w] : g[v]) {
      if(chmin(d[nv], d[v] + w * a)) { q.emplace(d[nv], nv); }
    }
  }
  while(!q.empty()) { q.pop(); }
  vector<ll> D(n, 1e18);
  D[n - 1] = 0;
  q.emplace(0, n - 1);
  while(!q.empty()) {
    auto [tmp, v] = q.top();
    q.pop();
    if(tmp > D[v]) { continue; }
    for(auto &[nv, w] : g[v]) {
      if(chmin(D[nv], D[v] + w * b + c)) { q.emplace(D[nv], nv); }
    }
  }
  ll r = 1e18;
  for(ll i = 0; i < n; i++) {
    r = min(r, d[i] + D[i]);
  }
  cout << r << "\n";
}
