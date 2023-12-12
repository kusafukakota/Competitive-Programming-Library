#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

auto mulall(vector<auto> &v) {
  ll n = ssize(v);
  queue<ll> q;
  for(ll i = 0; i < n; i++) { q.emplace(i); }
  while(ssize(q) >= 2) {
    ll x = q.front();
    q.pop();
    ll y = q.front();
    q.pop();
    v[x] = convolution(v[x], v[y]);
    q.emplace(x);
  }
  return v[q.front()];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, m;
  cin >> n >> m;

  vector<vector<mint>> v(m);
  for(ll i = 0, c; i < m; i++) {
    cin >> c;
    v[i].resize(c + 1);
    v[i][0] = 1;
    v[i][c] = -1;
  }

  auto f = mulall(v);

  mint r = 0;
  for(ll i = 0; i < n; i++) { r += mint(n) / (n - i) * f[i]; }
  if(m % 2 == 0) { r = -r; }

  cout << r.val() << "\n";
}
