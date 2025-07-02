#pragma once

#include <lib/PrimeFast.hpp>
#include <lib/Modpow.hpp>

ll phi(ll N) {
  ll ret = 1, last = -1;
  for(auto &i : PrimeFactorize(N)) {
    ret *= i - (last != i);
    last = i;
  }
  return ret;
}

ll PrimitiveRoot(ll N) {
  vector<ll> v;
  const ll ph = phi(N);
  for(auto &p : PrimeFactorize(ph)) {
    if(v.empty() || v.back() != p) { v.push_back(p); }
  }
  for(ll r = 1; r < N; r++) {
    if(gcd(N, r) != 1) { continue; }

    if(modpow(r, ph, N) != 1) { return -1; }
    bool ok = true;
    for(auto &i : v) {
      if(modpow(r, ph / i, N) == 1) {
        ok = false;
        break;
      }
    }
    if(ok) { return r; }
  }
  return -1;
}
