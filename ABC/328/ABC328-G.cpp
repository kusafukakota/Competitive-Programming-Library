#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, c;
  cin >> n >> c;
  vector<ll> a(n), b(n);
  for(auto &i : a) { cin >> i; }
  for(auto &i : b) { cin >> i; }

  vector<ll> dp(1 << n, 1e18);
  dp[0] = -c;
  for(ll i = 0; i < 1 << n; i++) {
    ll p = __builtin_popcountll(i);
    for(ll l = 0; l < n; l++) {
      for(ll r = l, cost = c; r < n; r++) {
        if(i & 1 << r) { break; }
        cost += abs(a[r] - b[p + r - l]);
        dp[i | ((1 << r + 1) - (1 << l))] = min(dp[i | ((1 << r + 1) - (1 << l))], dp[i] + cost);
      }
    }
  }
  cout << dp.back() << "\n";
}
