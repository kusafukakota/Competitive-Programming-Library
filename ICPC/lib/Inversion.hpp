#pragma once

#include <lib/Compress.hpp>

#include <atcoder/fenwicktree>
using namespace atcoder;

ll Inversion(vector<ll> &v, bool comp = false) {
  ll r = 0, n = v.size();
  if(comp) { Compress(v); }
  fenwick_tree<ll> b(n + 1);
  for(ll i = 0; i < n; i++) {
    r += b.sum(v[i] + 1, n + 1);
    b.add(v[i], 1);
  }
  return r;
}