#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }
  ll l[2], c[2], k[2];
  for(ll i = 0; i < 2; i++) { cin >> l[i] >> c[i] >> k[i]; }
  ll N = k[0] + 1;
  vector<vector<ll>> dp(n + 1, vector<ll>(N, 1e18));
  for(ll i = 0; i < N; i++) { dp[0][i] = 0; }
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < N; j++) {
      if(l[0] * j - v[i] >= l[0]) { break; }
      ll t = (v[i] - l[0] * j + l[1] - 1) / l[1];
      for(ll nx = N - j - 1; nx >= 0; nx--) {
        if(dp[i][nx] > k[1]) { break; }
        dp[i + 1][j + nx] = min(dp[i + 1][j + nx], dp[i][nx] + t);
      }
    }
  }
  ll r = 1e18;
  for(ll i = 0; i < N; i++) {
    if(dp[n][i] > k[1]) { continue; }
    r = min(r, i * c[0] + dp[n][i] * c[1]);
  }
  cout << (r == 1e18 ? -1 : r) << "\n";
}
