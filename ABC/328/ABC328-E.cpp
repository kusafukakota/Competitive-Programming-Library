#include <bits/stdc++.h>
using namespace std;
#include <atcoder/dsu>
using namespace atcoder;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m, k;
  cin >> n >> m >> k;
  vector<array<ll, 3>> e(m);
  for(auto &i : e) {
    for(auto &j : i) { cin >> j; }
    i[0]--, i[1]--;
    i[2] %= k;
  }

  ll ans = 1e18;
  if(m == n - 1) {
    ll t = 0;
    for(ll i = 0; i < n - 1; i++) {
      t += e[i][2];
      t %= k;
    }
    cout << t << "\n";
    return 0;
  }

  vector<bool> o(m, false);
  fill(o.end() - m + n - 1, o.end(), true);
  do {
    vector<ll> r;
    for(int i = 0; i < m; i++) {
      if(!o[i]) { r.push_back(i); }
    }
    dsu u(n);
    bool flag = true;
    ll tmp = 0;
    for(ll i = 0; i < n - 1; i++) {
      auto [a, b, w] = e[r[i]];
      if(u.same(a, b)) {
        flag = false;
        break;
      }
      u.merge(a, b);
      tmp += w;
      tmp %= k;
    }
    if(flag) { ans = min(ans, tmp % k); }
  } while(next_permutation(o.begin(), o.end()));
  cout << ans << "\n";
}
