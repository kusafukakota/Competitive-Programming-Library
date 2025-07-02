#pragma once

#include <atcoder/segtree>
using namespace atcoder;

namespace RMDQ {
constexpr ll INF = 1e18;
struct T {
  ll sum, val, l, r;
};
T op(T l, T r) { return {l.sum + r.sum, max({l.val, r.val, l.r + r.l}), max(l.l, l.sum + r.l), max(l.r + r.sum, r.r)}; }
T e() { return {0, -INF, -INF, -INF}; }
}  // namespace RMDQ

template<bool min = false> struct RangeMaximumDifferenceQuery {
  int N;
  vector<ll> v;
  segtree<RMDQ::T, RMDQ::op, RMDQ::e> S;
  RangeMaximumDifferenceQuery(const vector<ll> &v_): N(v_.size()), v(v_), S(N - 1) {
    for(ll i = 0; i < N - 1; i++) {
      ll x = v[i + 1] - v[i];
      if(min) { x = -x; }
      S.set(i, {x, x, x, x});
    }
  }
  void set(ll i, ll x) {
    v[i] = x;
    if(i) {
      ll d = v[i] - v[i - 1];
      if(min) { d = -d; }
      S.set(i - 1, {d, d, d, d});
    }
    if(i != N - 1) {
      ll d = v[i + 1] - v[i];
      if(min) { d = -d; }
      S.set(i, {d, d, d, d});
    }
  }
  ll prod(ll l, ll r) {
    return min ? -S.prod(l, r).val : S.prod(l, r).val;
  }
  ll all_prod() {
    return min ? -S.all_prod().val : S.all_prod().val;
  }
};