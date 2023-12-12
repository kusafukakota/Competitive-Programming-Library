#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ld> v(n);
  for(auto &i : v) { cin >> i; }
  vector<vector<long double>> dp(n + 1, vector<long double>(n + 1, -1e18));
  dp[0][0] = 0;
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j <= n; j++) {
      if(dp[i][j] < 0) { continue; }
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
      if(j != n) dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * 0.9 + v[i]);
    }
  }
  ld ans = -1e18, den = 0;
  for(ll i = 0; i < n; i++) {
    den = den * 0.9 + 1;
    ans = max(ans, dp[n][i + 1] / den - 1200.0 / sqrtl(i + 1));
  }
  cout << fixed << setprecision(16);
  cout << ans << "\n";
}
