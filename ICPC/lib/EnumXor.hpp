#pragma once

// L <= x ^ a < R となる x の区間 [l, r)の列挙
vector<pair<ll, ll>> EnumXor(uint64_t a, uint64_t L, uint64_t R) {
  vector<pair<ll, ll>> r;
  for(ll i = 0; i < 64; i++) {
    if(L == R) { break; }
    ll b = 1LL << i;
    if(L & b) {
      r.emplace_back(L ^ a, (L ^ a) + b);
      L += b;
    }
    if(R & b) {
      r.emplace_back((R - b) ^ a, ((R - b) ^ a) + b);
      R -= b;
    }
    if(a & b) { a ^= b; }
  }
  return r;
}