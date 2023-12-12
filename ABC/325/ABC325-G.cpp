#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, k;
  string s;
  cin >> s >> k;
  n = ssize(s);

  vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
  for(ll i = 0; i < n; i++) {
    for(ll j = i + 1; j <= n; j++) { dp[i][j] = j - i; }
  }
  for(ll l = n - 1; l >= 0; l--) {
    for(ll r = l + 1; r <= n; r++) {
      dp[l][r] = dp[l + 1][r] + 1;
      if(s[l] == 'o') {
        for(ll i = l; i < r; i++) {
          if(s[i] == 'f' && dp[l + 1][i] == 0) {
            dp[l][r] = min(dp[l][r], max(0LL, dp[i + 1][r] - k));
          }
        }
      }
    }
  }
  cout << dp[0][n] << "\n";
}

// 区間dp
