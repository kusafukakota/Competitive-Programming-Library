#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

constexpr ll COMAX = 100010;
mint fac[COMAX], finv[COMAX], inv[COMAX];
bool COMflag = false;

void COMINI() {
  COMflag = true;
  fac[0] = finv[0] = inv[0] = 1;
  for(ll i = 0; i < COMAX - 1; i++) { fac[i + 1] = fac[i] * (i + 1); }
  finv[COMAX - 1] = 1 / fac[COMAX - 1];
  for(ll i = COMAX - 2; i >= 1; i--) { finv[i] = finv[i + 1] * (i + 1); }
  for(ll i = 0; i < COMAX - 1; i++) { inv[i + 1] = finv[i + 1] * fac[i]; }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  COMINI();

  ll n, m;
  cin >> n >> m;

  vector<ll> r(n, 0), b(n, 0);
  for(ll i = 0, pos; i < m; i++) {
    cin >> pos;
    pos--;
    r[pos]++;
  }
  for(ll i = 0, pos; i < m; i++) {
    cin >> pos;
    pos--;
    b[pos]++;
  }

  vector<ll> sr(1 << n, 0), sb(1 << n, 0);
  for(ll i = 0; i < 1 << n; i++) {
    for(ll j = 0; j < n; j++) {
      if(i & 1 << j) {
        sr[i] += r[j];
        sb[i] += b[j];
      }
    }
  }

  vector<mint> dp(1 << n, 0);
  mint ans = 0;
  for(ll i = 1; i < 1 << n; i++) {
    if(sr[i] != sb[i]) { continue; }
    dp[i] = fac[sr[i]];
    for(ll j = i; j > i - j; j = (j - 1) & i) {
      if(j == i) { continue; }
      if(sr[j] != sb[j] || sr[i ^ j] != sb[i ^ j]) { continue; }
      dp[i] -= dp[j] * fac[sr[i ^ j]];
    }
    ans += dp[i] * fac[m - sr[i]];
  }
  ans *= finv[m];
  cout << ans.val() << "\n";
}

// 部分集合dp
