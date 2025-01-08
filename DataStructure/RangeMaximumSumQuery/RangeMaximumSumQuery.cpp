constexpr ll INF = 1e18;
struct T {
  ll sum, val, l, r;
};
T op(T l, T r) { return {l.sum + r.sum, max({l.val, r.val, l.r + r.l}), max(l.l, l.sum + r.l), max(l.r + r.sum, r.r)}; }
T e() { return {0, -INF, -INF, -INF}; }

template<bool min = false> struct RangeMaximumSumQuery {
  segtree<T, op, e> S;
  RangeMaximumSumQuery(const vector<ll> &v): S(v.size()) {
    for(int i = 0; i < (int)v.size(); i++) { set(i, v[i]); }
  }
  void set(ll i, ll x) {
    if(min) { x = -x; }
    S.set(i, {x, x, x, x});
  }
  ll prod(ll l, ll r) { return min ? -S.prod(l, r).val : S.prod(l, r).val; }
  ll all_prod() { return min ? -S.all_prod().val : S.all_prod().val; }
};
