#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

struct S {
  mint x, s;
};
struct F {
  mint x, s;
};
S op(S a, S b) { return {0, 0}; }
S e() { return {1, 0}; }
S fx(F f, S x) {
  mint nx, ns;
  nx = x.x * f.x;
  ns = x.s + x.x * f.s;
  return {nx, ns};
}
F fg(F f, F g) { return {f.x * g.x, g.s + g.x * f.s}; }
F id() { return {1, 0}; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll N, M;
  cin >> N >> M;

  vector<ll> A(N);
  for(auto &i : A) { cin >> i; }

  vector<tuple<ll, ll, ll>> Q(M);
  for(auto &[L, R, X] : Q) {
    cin >> L >> R >> X;
    L--;
  }
  ranges::reverse(Q);

  vector<S> v(N, e());
  lazy_segtree<S, op, e, F, fx, fg, id> seg(v);

  for(auto &[L, R, X] : Q) {
    mint x = mint(R - L).inv();
    seg.apply(L, R, {1 - x, X * x});
  }

  for(ll i = 0; i < N; i++) { seg.apply(i, {1, A[i]}); }

  for(ll i = 0; i < N; i++) { cout << seg.get(i).s.val() << " "; }
}
