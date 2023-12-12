#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, x;
  cin >> n >> x;
  vector<ll> v(n);
  for(auto &i : v) { cin >> i; }

  mint inv = mint(n).inv();
  vector<mint> dp(x + 1, 0);
  dp[0] = 1;
  mint r = 0;
  for(ll i = 0; i <= x; i++) {
    if(i + v[0] > x) { r += dp[i] * inv; }
    for(ll j = 0; j < n; j++) {
      if(i + v[j] <= x) { dp[i + v[j]] += dp[i] * inv; }
    }
  }
  cout << r.val() << "\n";
}
