#pragma once

#include <lib/Inversion.hpp>

ll SwapMatch(vector<ll> &A, vector<ll> &B, bool check = false) {
  if(check) {
    auto a = A, b = B;
    ranges::sort(a);
    ranges::sort(b);
    if(a != b) { return -1; }
  }
  if(A.empty()) { return 0; }
  auto a = A, b = B;
  Compress(a);
  Compress(b);
  ll N = A.size();
  vector<queue<ll>> q(ranges::max(a) + 1);
  vector<ll> v;
  for(ll i = 0; i < N; i++) { q[a[i]].emplace(i); }
  for(ll i = 0; i < N; i++) {
    v.emplace_back(q[b[i]].front());
    q[b[i]].pop();
  }
  return Inversion(v);
}