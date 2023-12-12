#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll = long long;

struct S {
  ll mx[2], l[2], r[2], len;
};
using F = ll;
S op(S a, S b) {
  S r;
  for(ll i = 0; i < 2; i++) {
    r.mx[i] = max({a.mx[i], b.mx[i], a.r[i] + b.l[i]});
    r.l[i] = a.l[i];
    if(a.l[i] == a.len) { r.l[i] += b.l[i]; }
    r.r[i] = b.r[i];
    if(b.r[i] == b.len) { r.r[i] += a.r[i]; }
    r.len = a.len + b.len;
  }
  return r;
}
S e() {
  S r;
  for(ll i = 0; i < 2; i++) { r.mx[i] = r.l[i] = r.r[i] = 0; }
  r.len = 0;
  return r;
}
S fx(F f, S x) {
  if(f) {
    swap(x.mx[0], x.mx[1]);
    swap(x.l[0], x.l[1]);
    swap(x.r[0], x.r[1]);
  }
  return x;
}
F fg(F f, F g) { return f ^ g; }
F id() { return 0; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, q;
  string s;
  cin >> n >> q >> s;
  vector<S> v(n);
  for(ll i = 0; i < n; i++) {
    ll t = s[i] - '0';
    for(ll j = 0; j < 2; j++) { v[i].mx[j] = v[i].l[j] = v[i].r[j] = j ^ t ^ 1; }
    v[i].len = 1;
  }
  lazy_segtree<S, op, e, F, fx, fg, id> seg(v);
  while(q--) {
    ll c, l, r;
    cin >> c >> l >> r;
    l--;
    if(c == 1) { seg.apply(l, r, 1); }
    else { cout << seg.prod(l, r).mx[1] << "\n"; }
  }
}
