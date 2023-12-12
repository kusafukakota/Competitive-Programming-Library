#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }
  mint inv = mint(1) / n;
  vector<mint> dp(n + 1, 0);
  dp[0] = 1;
  mint s = 1;
  for(ll i = 0; i < n; i++) {
    dp[i + 1] = s * inv;
    s += dp[i + 1];
  }
  mint r = 0;
  for(ll i = 0; i < n; i++) { r += dp[i + 1] * v[i]; }
  cout << r.val() << "\n";
}
