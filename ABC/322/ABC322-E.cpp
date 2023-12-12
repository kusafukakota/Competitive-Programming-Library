#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = 1LL << 60;

vector<ll> n_BASE(ll x, ll n, bool re = 0) {
  vector<ll> r;
  while(x != 0) {
    r.emplace_back(x % n);
    (x -= (x % n)) /= n;
  }
  if(re) ranges::reverse(r);
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, k, p;
  cin >> n >> k >> p;
  vector<ll> c(n);
  vector<vector<ll>> v(n, vector<ll>(k));
  for(ll i = 0; i < n; i++) {
    cin >> c[i];
    for(auto &j : v[i]) { cin >> j; }
  }
  ll s = powl(p + 1, k);
  vector<vector<ll>> dp(n + 1, vector<ll>(s, INF));
  dp[0][0] = 0;
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < s; j++) {
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
      auto bit = n_BASE(j, p + 1);
      bit.resize(k);
      ll nx = 0;
      for(ll l = 0; l < k; l++) {
        ll t = min(bit[l] + v[i][l], p);
        nx += t * powl(p + 1, l);
      }
      dp[i + 1][nx] = min(dp[i + 1][nx], dp[i][j] + c[i]);
    }
  }
  cout << (dp[n].back() == INF ? -1 : dp[n].back()) << "\n";
}
