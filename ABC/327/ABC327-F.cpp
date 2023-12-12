#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree>
using namespace atcoder;
using ll = long long;

using S = ll;
using F = ll;
S op(S l, S r) { return max(l, r); }
S e_() { return -1e18; }
S fx(F f, S x) { return f + x; }
F fg(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, d, w;
  cin >> n >> d >> w;
  vector<vector<ll>> x(200010);
  for(ll i = 0, a, b; i < n; i++) {
    cin >> a >> b;
    x[a].emplace_back(b);
  }
  lazy_segtree<S, op, e_, F, fx, fg, id> seg(200010);
  for(ll i = 0; i < 200010; i++) { seg.set(i, 0); }
  for(ll i = 0; i < d; i++) {
    for(auto &j : x[i]) { seg.apply(max(0LL, j - w + 1), j + 1, 1); }
  }
  ll ans = seg.all_prod();
  for(ll i = 0; i + d < 200010; i++) {
    for(auto &j : x[i]) { seg.apply(max(0LL, j - w + 1), j + 1, -1); }
    for(auto &j : x[i + d]) { seg.apply(max(0LL, j - w + 1), j + 1, 1); }
    ans = max(ans, seg.all_prod());
  }
  cout << ans << "\n";
}
