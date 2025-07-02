#pragma once

ll MaxSubsetXor(vector<ll> v) {
  ll N = v.size(), idx = 0;
  for(ll i = 60; i >= 0; i--) {
    ll midx = idx, mx = -1e18;
    for(ll j = idx; j < N; j++) {
      if(v[j] & (1LL << i) && v[j] > mx) {
        mx = v[j];
        midx = j;
      }
    }
    if(mx == -1e18) { continue; }
    swap(v[idx], v[midx]);
    midx = idx;
    for(ll j = 0; j < N; j++) {
      if(j != midx && v[j] & (1LL << i)) { v[j] ^= v[midx]; }
    }
    idx++;
  }
  ll r = 0;
  for(ll i = 0; i < N; i++) { r ^= v[i]; }
  return r;
}