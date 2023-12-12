#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<vector<tuple<ll, ld, ld>>> g(n);
  for(ll i = 0; i < m; i++) {
    ll u, v;
    ld b, c;
    cin >> u >> v >> b >> c;
    u--, v--;
    g[u].emplace_back(make_tuple(v, b, c));
  }
  for(long double L = 0, R = 1e10;;) {
    if(R - L <= 1e-12) {
      cout << fixed << setprecision(12);
      cout << L << "\n";
      break;
    }
    long double M = (L + R) / 2;
    vector<long double> dp(n, -(1e18));
    dp[0] = 0;
    for(ll i = 0; i < n; i++) {
      for(auto &[nv, b, c] : g[i]) { dp[nv] = max(dp[nv], dp[i] + b - c * M); }
    }
    dp[n - 1] >= 0 ? L = M : R = M;
  }
}
