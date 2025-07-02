#pragma once

#include <lib/PrimeFast.hpp>

// i∈[1, n] で gcd(i, k) == first となるものの個数/総和を求める <sum = false, T = ll>
template<bool sum = false, typename T = ll> vector<pair<ll, T>> GcdCount(ll n, ll k) {
  auto p = PrimeFactorize(k);
  auto div = Divisor(p);
  p.erase(unique(p.begin(), p.end()), p.end());
  ll s = p.size();
  vector<pair<ll, bool>> e;
  for(ll i = 0; i < 1 << s; i++) {
    ll t = 1;
    bool odd = false;
    for(ll j = 0; j < s; j++) {
      if(i & 1 << j) {
        t *= p[j];
        odd = !odd;
      }
    }
    e.emplace_back(t, odd);
  }

  vector<pair<ll, T>> ret;
  for(auto &i : div) {
    T r = 0, tmp;
    ll K = k / i, N = n / i, cnt;
    for(auto &[t, odd] : e) {
      if(K % t) { continue; }
      cnt = N / t;
      if(!sum) { tmp = cnt; }
      else { tmp = T(cnt + 1) * cnt * t * i / 2; }
      r += odd ? -tmp : tmp;
    }
    ret.emplace_back(i, r);
  }
  return ret;
}