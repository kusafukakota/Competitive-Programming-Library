#pragma once

ll modpow(ll x, auto n, ll p) {
  ll r = 1;
  while(n) {
    if(n & 1) { r = (__int128_t)r * x % p; }
    x = (__int128_t)x * x % p;
    n >>= 1;
  }
  return r;
}
